#pragma once

#include <Core/Core.h>
#include <Math/Vector2.h>
#include <Math/Color.h>
#include <Core/CraftObject.h>
#include <memory>	
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
	
	/* 게임플레이 이벤트 */	
	public:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();
		virtual void OnCollision(const std::shared_ptr<Actor>& other);

		virtual void Destroy();
		void QuitGame(); // 엔진 종료 TODO : GameManager에서 관리
		
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		inline bool IsActive() const { return isActive && !hasExpired; }
		inline bool HasExpired() const { return hasExpired; }
		
	protected:
		bool hasBeganPlay = false;
		bool isActive = true;
		bool hasExpired = false;
		
		
		
	/* 액터 소유자 레벨 */				
	public:
		inline std::shared_ptr<Level> GetOwner() const { return owner.lock(); }		
		void SetOwner(std::weak_ptr<Level> newOwner);
		
	protected:
		// 이 액터를 소유하는 레벨 객체에 대한 weak_ptr
		std::weak_ptr<Level> owner;
		
		
		
	/* Actor 위치정보 (Transform->Position) */			
	public:
		// 현재 위치
		Vector2 GetPosition() const;
		Vector2 GetWorldPosition() const;
		void SetPosition(const Vector2& newPosition);

		// 이전 위치
		Vector2 GetPreviousPosition() const;
		void SavePreviousPosition();			
		
		
		
	/* Scene Graph Section */		
	public:
		// Scene Graph에서 부모 Actor를 지정하는 함수
		void AttachTo(
			const std::shared_ptr<Actor>& newParent,
			bool keepWorldPosition = true  
			);
		
		// 부모 Actor의 연결을 해제하는 함수
		void DetachFromParent();
		
		
	/* Component Section */		
	public:		
		// Actor에 Component를 추가 요청
		template<typename T, typename... Args,
		typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::shared_ptr<T> AddComponent(Args&&... args)
		{
			// TransformComponent의 경우 액터 생성자에서 이미 만들어지므로 중복생성 방지
			static_assert(!std::is_same<T, TransformComponent>::value, "TransformComponent should be created by an Actor Constructor");
			
			// 새로운 컴포넌트 생성후 추가요청 목록에 등록
			std::shared_ptr<T> newComponent = std::make_shared<T>(std::forward<Args>(args)...);
			addRequestedComponentList.emplace_back(newComponent);	
			
			// 생성한 컴포넌트 반환
			return newComponent;			
		}
		
		// Actor에 존재하는 컴포넌트를 검색
		template<typename T, 
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
		
		// 부모 액터 Getter
		inline std::shared_ptr<Actor> GetParent() const { return parent.lock(); }
		
		// 자식 액터 목록 Getter
		inline const std::vector<std::weak_ptr<Actor>>& GetChildren() const { return children; }
		
		// Transform 컴포넌트 접근 Getter
		inline std::shared_ptr<TransformComponent> GetTransform() const { return transform; }
		
	protected:
		// 추가 요청된 Component를 실제 목록에 추가처리 함수
		void ProcessAddComponents();
		
		// Component->Actor 오너십 설정 함수
		void BindComponentOwners();
		
	protected:		
		// Actor에 추가된 컴포넌트 목록
		std::vector<std::shared_ptr<Component>> componentList;
		
		// 추가 요청된 컴포넌트 목록 
		std::vector<std::shared_ptr<Component>> addRequestedComponentList;
		
		// Scene Graph에서 부모 Actor
		std::weak_ptr<Actor> parent;
		
		// Scene Graph에서 자식 Actor 목록
		std::vector<std::weak_ptr<Actor>> children;				
		
		// 위치 컴포넌트 (액터 필수 보유)
		std::shared_ptr<TransformComponent> transform;
	};
}
