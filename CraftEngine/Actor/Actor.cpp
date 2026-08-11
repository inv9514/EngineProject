#include "Actor.h"
#include <Engine/Engine.h>
#include <Render/Renderer.h>

namespace Craft
{
	Actor::Actor(const std::string& image, const Vector2& position, Color color)
		: image(image), position(position), color(color),
		width(static_cast<int>(image.length())) // TODO : Height추가
	{
		
	}

	Actor::~Actor()
	{
		
	}

	void Actor::BeginPlay()
	{
		hasBeganPlay = true;
	}

	void Actor::Tick(float deltaTime)
	{
		
	}

	void Actor::Draw()
	{
		// Renderer에 드로우 데이터 제출  
		if (!IsActive()) return;		
		Renderer::Get().Submit(image, position, color, sortingOrder);
	}

	void Actor::OnCollision(const std::shared_ptr<Actor>& other)
	{
		/* 엔진의 Run중 도중 collisionSystem->ProcessCollision 으로 호출
		 * 엔진은 메인 레벨의 모든 액터를 상대로, 현재/이전 위치를 체크 후 최악을 상정해 겹쳐있는 액터를 전부 저장함
		 * 그 후 저장된 액터의 OnCollision을 양쪽 모두에게 호출
		 * 세부 내용은 해당 액터에서, 상태 액터의 타입을 검사해 타입별로 다른 행동문 작성  
		 * 주의 : 한쪽이 다른쪽을 Destroy()하는 등 이미 처리한다면, 다른쪽에서는 행동 지정 x */
	}

	void Actor::Destroy()
	{
		// 삭제 플래그 : 레벨에서 검사하고 다음프레임 전에 액터 제거
		hasExpired = true;
	}

	void Actor::QuitGame()
	{
		Engine::Get().Quit();
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		// 변경하려는 위치 값이 기존 값과 동일하면 새로 설정할 필요 없이 리턴
		if (position == newPosition) return;

		position = newPosition;
	}
}