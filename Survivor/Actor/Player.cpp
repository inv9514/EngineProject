#include "Player.h"

#include <iostream>
#include <ostream>
#include <Render/Renderer.h>
#include <Input/Input.h>
#include <Engine/Engine.h>
#include <Level/Level.h>

#include "Level/GameLevel.h"

using namespace Craft;

Player::Player()
    : Actor("V", Vector2::Zero, Color::Yellow)
{
    // 플레이어 스폰 위치설정
    SetPosition(Vector2::Zero);
    
    positionX = 0;
    positionY = 0;
    
    sortingOrder = 10;    
}

void Player::Tick(float deltaTime)
{
    super::Tick(deltaTime);
    
    float directionX = 0.f;
    float directionY = 0.f;
    
    if (Input::Get().GetKey(VK_RIGHT))
    {
        directionX = 1.f;
    }
    if (Input::Get().GetKey(VK_LEFT))
    {
        directionX = -1.f;
    }
    if (Input::Get().GetKey(VK_DOWN))
    {
        directionY = 1.f;
    }
    if (Input::Get().GetKey(VK_UP))
    {
        directionY = -1.f;
    }
    
    
    Move(directionX, directionY, deltaTime);   
}

void Player::OnCollision(const std::shared_ptr<Actor>& other)
{
    
    
}

void Player::Move(float directionX, float directionY, float deltaTime)
{
    // 새로운 위치값 구하고 클램핑 제거
    positionX += directionX * moveSpeed * deltaTime;
    if (positionX + width >= Engine::Get().GetWidth()) positionX = static_cast<float>(Engine::Get().GetWidth() - width);
    
    positionY += directionY * moveSpeed * deltaTime;
    
    // 새로운 위치로 업데이트
    Vector2 newPosition = GetPosition();
    newPosition.x = static_cast<int>(positionX);
    newPosition.y = static_cast<int>(positionY);
    SetPosition(newPosition);
    
    std::shared_ptr<Level> owner = GetOwner();

    if (owner && owner->IsTypeOf<GameLevel>())
    {
        std::shared_ptr<GameLevel> gameLevel = Cast<GameLevel>(owner);

        gameLevel->GetCamera()->SetPosition(GetPosition());
    }
}

void Player::Draw()
{
    /* 기존 Draw : 액터의 position이 콘솔의 절대좌표 기준
        if (!IsActive()) return;		
        Renderer::Get().Submit(image, position, color, sortingOrder);  */
     
    /* 재정의한 Draw : Camera와 연계해서 Submit 하기전에 position의 벡터를 변환하고 Submit */    
    // 비활성 상태라면 그리지 않음.
    if (!IsActive()) return;

    // 자신을 소유한 Level 가져오기.
    std::shared_ptr<Level> owner = GetOwner();

    // 기본적으로는 자신의 월드 좌표를 사용.
    Vector2 screenPosition = position;

    if (owner && owner->IsTypeOf<GameLevel>())  // TODO : 이거 Tick단위 호출인데 캐스팅비용 크지않나?
    {
        // Level을 GameLevel로 형변환.
        std::shared_ptr<GameLevel> gameLevel = Craft::Cast<GameLevel>(owner);

        // Camera를 이용해 월드 좌표 → 화면 좌표 변환.
        screenPosition = gameLevel->GetCamera()->ConvertWorldToScreen(position);
    }

    // 변환된 화면 좌표로 렌더링 요청.
    Renderer::Get().Submit(image, screenPosition, color, sortingOrder); 
}

