#include "Player.h"
#include <Component/BoxCollisionComponent.h>
#include <Engine/Engine.h>
#include <Level/Level.h>
#include <Input/Input.h>

#include <Component/RelativeSpriteRendererComponent.h>

using namespace Craft;

namespace
{
    int GetCollisionWidth(const Actor& actor)
    {
        std::shared_ptr<BoxCollisionComponent> collision = actor.GetComponent<BoxCollisionComponent>();
        return collision ? collision->GetWidth() : 0;
    }
}


Player::Player()
    : Actor(Vector2::Zero)
{
    // 컴포넌트 추가 
    AddComponent<RelativeSpriteRendererComponent>("V", Color::Yellow, 5);
    AddComponent<BoxCollisionComponent>(1);
	
    // 생성 위치 설정
    int x = (Engine::Get().GetWidth() / 2);
    int y = (Engine::Get().GetHeight() / 2);
    SetPosition(Vector2(x, y));

    // 현재위치 저장 
    positionX = static_cast<float>(x);
    positionY = static_cast<float>(y);
}

void Player::BeginPlay()
{
    super::BeginPlay();
}

void Player::Tick(float deltaTime)
{
    super::Tick(deltaTime);
    
    if (Input::Get().GetKeyDown(VK_ESCAPE))
    {
        QuitGame();
    }
    
    float directionX = 0.0f;
    float directionY = 0.0f;
    
    if (Input::Get().GetKey(VK_RIGHT))
    {
        directionX = 1.0f;
    }
    if (Input::Get().GetKey(VK_LEFT))
    {
        directionX = -1.0f;
    }
    if (Input::Get().GetKey(VK_UP))
    {
        directionY = -1.0f;
    }
    if (Input::Get().GetKey(VK_DOWN))
    {
        directionY = 1.0f;
    }

    Move(directionX, directionY, deltaTime);
}

void Player::OnCollision(const std::shared_ptr<Actor>& other)
{
    super::OnCollision(other);
}

void Player::Move(float directionX, float directionY, float deltaTime)
{
    positionX = positionX + directionX * moveSpeed * deltaTime;
    positionY = positionY + directionY * moveSpeed * deltaTime / 2;

    Vector2 newPosition;
    newPosition.x = static_cast<int>(positionX);
    newPosition.y = static_cast<int>(positionY);
    SetPosition(newPosition);    
}
