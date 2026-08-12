#pragma once

#include <Core/Core.h>
#include <Math/Vector2.h>
#include <Math/Color.h>
#include <Core/CraftObject.h>
#include <memory>	
#include <string>
#include <vector>

#include "Component/Component.h"
#include "Component/TransformComponent.h"

namespace Craft
{
	class CRAFT_API Actor : public CraftObject, public std::enable_shared_from_this<Actor>
	{
		TYPE_DECLARATIONS(Actor, CraftObject)
		
		friend class Level;

	public:
		Actor(const Vector2& position = Vector2::Zero);		
		virtual ~Actor();
	
		// 게임플레이 이벤트 함수 
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// 충돌 이벤트 함수
		virtual void OnCollision(const std::shared_ptr<Actor>& other);

		void Destroy();

		// 엔진 종료요청 (주로 상속받은 Player에서) TODO : 이거그냥 레벨이 종료조건을 갖고있는게 낫지않나?
		void QuitGame();

		// 액터가 본인을 소유한 레벨에 접근하기 위한 weak_ptr
		inline std::shared_ptr<Level> GetOwner() const { return owner.lock(); }
		void SetOwner(std::weak_ptr<Level> newOwner);

		// 액터의 현재 위치값 Getter / Setter
		Vector2 GetPosition() const;
		Vector2 GetWorldPosition() const;
		void SetPosition(const Vector2& newPosition);

		// 액터의 이전 위치값 Getter / Setter 
		Vector2 GetPreviousPosition() const;
		void SavePreviousState();
		
		// Scene Graph에서 부모 Actor를 지정하는 함수
		void AttachTo(
			const std::shared_ptr<Actor>& newParent,
			bool keepWorldPosition = true
			);
		
		// 부모 Actor의 연결을 해제하는 함수
		void DetachFromParent();

		// Actor에 Component를 추가 요청
		template<typename T, typename... Args,
		typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::shared_ptr<T> AddComponent(Args&&... args)
		{
			// TransformComponent는 액터 생성자에서 이미 만들어지므로 중복생성 체크
			static_assert(!std::is_same<T, TransformComponent>::value, "TransformComponent should be created by an Actor Constructor");
			
			// 새로운 컴포넌트 생성후 추가요청 목록에 등록
			std::shared_ptr<T> newComponent = std::make_shared<T>(std::forward<Args>(args)...);
			addRequestedComponentList.emplace_back(newComponent);	
			
			// 생성한 컴포넌트 반환
			return newComponent;			
		}
		
		// Actor에 존재하는 컴포넌트를 검색
		template<typename T, typename... Args,
		typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::shared_ptr<T> GetComponent() const
		{
			// 컴포넌트 목록과 요청 목록을 전부 순회해 컴포넌트 T를 검색하고 반환
			for (const std::shared_ptr<Component>& component : componentList)
			{
				if (component && component->IsTypeOf<T>()) return std::static_pointer_cast<T>(component);
			}
			for (const std::shared_ptr<Component>& component : addRequestedComponentList)
			{
				if (component && component->IsTypeOf<T>()) return std::static_pointer_cast<T>(component);
			}
	
			// 두 리스트에 모두 없다면 return null 
			return nullptr;
		}
		
		// 플래그 접근 Getter
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		inline bool IsActive() const { return isActive && !hasExpired; }
		inline bool HasExpired() const { return hasExpired; }
		
		// 컴포넌트 접근 Getter
		inline std::shared_ptr<TransformComponent> GetTransform() const { return transform; }
	
		// 부모 Actor 반환 함수
		inline std::shared_ptr<Actor> GetParent() const { return parent.lock(); }
		
		// 자식 Actor 목록 반환 함수
		inline const std::vector<std::weak_ptr<Actor>>& GetChildren() const {return children; }

	protected:
		// 추가 요청된 Component를 실제 목록에 추가처리 함수
		void ProcessAddComponents();
		
		// Component->Actor 오너십 설정 함수
		void BindComponentOwners();
		
	protected:
		// 액터 플래그
		bool hasBeganPlay = false;

		bool isActive = true;

		bool hasExpired = false;

		// 이 액터를 소유하는 레벨 객체에 대한 weak_ptr
		std::weak_ptr<Level> owner;
		
		// 위치 컴포넌트
		std::shared_ptr<TransformComponent> transform;
		
		// Actor에 추가된 컴포넌트 목록
		std::vector<std::shared_ptr<Component>> componentList;
		
		// 추가 요청된 컴포넌트 목록 
		std::vector<std::shared_ptr<Component>> addRequestedComponentList;
		
		// Scene Graph에서 부모 Actor
		std::weak_ptr<Actor> parent;
		
		// Scene Graph에서 자식 Actor 목록
		std::vector<std::weak_ptr<Actor>> children;				
	};
}
