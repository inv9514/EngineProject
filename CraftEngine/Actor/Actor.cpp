#include "Actor.h"
#include <Engine/Engine.h>
#include <Render/Renderer.h>

namespace Craft
{
	Actor::Actor(const Vector2& position)
	{
		// Transform는 모든 액터가 반드시 보유하므로 생성자에서 함께 컴포넌트 생성
		transform = std::make_shared<TransformComponent>(position);
	}
	
	Actor::~Actor()
	{
		
	}

	void Actor::BeginPlay()
	{
		// 중복 호출 방지를 위한 플래그설정
		hasBeganPlay = true;
		
		// Actor의 BeginPlay를 보유한 Component에 전달
		for (const std::shared_ptr<Component>& component : componentList)
		{
			if (!component->HasBeganPlay()) component->BeginPlay();
		}
	}

	void Actor::Tick(float deltaTime)
	{
		if (!IsActive()) return;	
		
		// Actor의 Tick 이벤트를 Component에 전달
		for (const std::shared_ptr<Component>& component : componentList)
		{
			component->Tick(deltaTime);
		}
	}

	void Actor::Draw()
	{
		if (!IsActive()) return;		
		
		// Actor의 Draw 이벤트를 Component에 전달
		for (const std::shared_ptr<Component>& component : componentList)
		{
			// 다른 컴포넌트의 Draw()는 비워져있지만 SpriteComponent는 Submit을 함
			component->Draw();  
		}
	}

	void Actor::OnCollision(const std::shared_ptr<Actor>& other)
	{
		/* 엔진의 Run중 도중 collisionSystem->ProcessCollision 으로 호출
		 * 엔진은 메인 레벨의 모든 액터를 상대로, 현재/이전 위치를 체크 후 최악을 상정해 겹쳐있는 액터를 전부 저장함
		 * 그 후 저장된 액터의 OnCollision을 양쪽 모두에게 호출
		 * 세부 내용은 해당 액터에서, 상태 액터의 타입을 검사해 타입별로 다른 행동문 작성  
		 * 주의 : 한쪽이 다른쪽을 Destroy()하는 등 이미 처리한다면, 다른쪽에서는 행동 지정 x */
		
		if (!IsActive()) return;
		
		// Actor의 Collision 이벤트를 Component에 전달
		for (const std::shared_ptr<Component>& component : componentList)
		{
			component->OnCollision(other);
		}
		
	}

	void Actor::Destroy()
	{
		// 삭제 플래그 : 레벨에서 검사하고 다음프레임 전에 액터 제거
		hasExpired = true;
		
		// 자식 Actor가 있다면 자신 액터들도 함께 제거
		for (const std::weak_ptr<Actor>& child : children)
		{
			std::shared_ptr<Actor> childActor = child.lock();
			if (childActor) childActor->Destroy();
		}
	}

	void Actor::QuitGame()
	{
		Engine::Get().Quit();
	}

	void Actor::SavePreviousState()
	{
		// 충돌을 위해 액터의 이전 위치값을 기억하는 기능은 transform에 위임
		if (transform) transform->SavePreviousWorldPosition();
	}

	void Actor::AttachTo(const std::shared_ptr<Actor>& newParent, bool keepWorldPosition)
	{
		// 부모가 없거나 부모로 설정할 포인터를 읽었더니 자신이면 스킵
		if (!newParent || newParent.get() == this) return;
		
		// 기존에 부모가 있다면 제거
		DetachFromParent();
		
		// 새로운 부모 설정
		parent = newParent;
		newParent->children.emplace_back(weak_from_this());
		
		// 위치 설정
		if (transform && newParent->GetTransform())
		{
			// 부모와의 연결 전, 트랜스폼의 월드위치 저장 T1 
			Vector2 worldPosition = transform->GetWorldPosition();
			
			// 트랜스폼의 부모 설정
			transform->SetParent(newParent->GetTransform());
			
			// 두번째 파라미터 bool에 따른 선택사항 처리
			if (keepWorldPosition) transform->SetWorldPosition(worldPosition);
		}
	}

	void Actor::DetachFromParent()
	{
		// 기존 부모 확인
		std::shared_ptr<Actor> oldParent = parent.lock();

		// 기존 부모의 자식목록에서 this를 제거
		if (oldParent)
		{
			// 부모의 모든 자손목록을 대상으로
			auto& siblingList = oldParent->children;
			for (auto iterator = siblingList.begin(); iterator != siblingList.end(); ++iterator)
			{
				// 자손목록중 자신을 발견하면 제거하고 루프 탈출
				if ((*iterator).lock().get() == this)
				{
					siblingList.erase(iterator);
					break;
				}
			}
		}
		
		// 제거후 기존 부모참조 변수 초기화
		parent.reset();
		
		if (transform)
		{
			// 부모와의 연결 후 화면위치 유지
			Vector2 worldPosition = transform->GetWorldPosition();
			transform->SetParent(std::weak_ptr<TransformComponent>());
			transform->SetWorldPosition(worldPosition);  
		}
		
	}

	void Actor::SetOwner(std::weak_ptr<Level> newOwner)
	{
		// 액터의 Owner를 레벨로 설정
		owner = newOwner;
		
		// 보유한 Component들의 Owner를 자신으로 설정
		BindComponentOwners();	
	}

	Vector2 Actor::GetPosition() const
	{
		// 트랜스폼의 localPosition을 받아와 리턴
		return transform ? transform->GetLocalPosition() : Vector2::Zero;
	}

	Vector2 Actor::GetWorldPosition() const
	{
		// 트랜스폼의 WorldPosition을 받아와 리턴
		return transform ? transform->GetWorldPosition() : Vector2::Zero;	
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		// 변경하려는 위치 값이 기존 값과 동일하면 새로 설정할 필요 없이 리턴
		if (GetPosition() == newPosition) return;
		
		if (transform) transform->SetLocalPosition(newPosition);
	}

	Vector2 Actor::GetPreviousPosition() const
	{
		// 트랜스폼의 이전 WorldPosition을 받아와 리턴 
		return transform ? transform->GetPreviousWorldPosition() : Vector2::Zero;
	}

	void Actor::ProcessAddComponents()
	{
		if (addRequestedComponentList.empty()) return;
		
		BindComponentOwners(); // 컴포넌트의 Owner를 현재 액터로 설정
		
		for (const std::shared_ptr<Component>& component : addRequestedComponentList)
		{
			if (!component) continue;
			
			// 요청목록을 실제 컴포넌트 목록이 추가
			componentList.emplace_back(component);  
			
			// Actor가 이미 BeginPlay를 처리했다면 추가된 컴포넌트에서도 BeginPlay 호출
			if (hasBeganPlay && !component->HasBeganPlay())
			{
				component->BeginPlay();
			}
		}
		
		// 추가 완료 후 요청목록 초기화
		addRequestedComponentList.clear();
	}

	void Actor::BindComponentOwners()
	{
		// actor는 현재 객체(자신)의 포인터 
		std::shared_ptr<Actor> actor = shared_from_this();
		if (!actor) return;
		
		// transform 컴포넌트는 생성자에서 만들어지므로 요청목록, 컴포넌트목록에 들어가지 않으므로 따로 처리
		if (transform) transform->SetOwner(actor);
		
		// 컴포넌트 목록, 요청 목록 위치가 다를뿐 둘다 가리키는 대상은 실존하는 컴포넌트이므로
		for (const std::shared_ptr<Component>& component : componentList)
		{
			if (component) component->SetOwner(actor);
		}
		
		// 새로운 컴포넌트가 있으면(!addRequestedComponentList.empty()) 두 목록을 가리지 않고 오너십 설정
		for (const std::shared_ptr<Component>& component : addRequestedComponentList)
		{
			if (component) component->SetOwner(actor);
		}
 	}
}
