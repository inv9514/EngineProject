#include "Player.h"

#include <Input/Input.h>
#include <Engine/Engine.h>

using namespace Craft;

Player::Player()
    : Actor("PPP\nPPP\nPPP", Vector2::Zero, Color::Yellow)
{
    // 플레이어 스폰 위치설정
    int x = (Engine::Get().GetWidth() / 2) - (width / 2);
    int y = (Engine::Get().GetHeight() - 2);
    SetPosition(Vector2(x, y));
    
    positionX = static_cast<float>(x);
    positionY = static_cast<float>(y);
    
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
    // 새로운 위치값 구하고 클램핑
    positionX += directionX * moveSpeed * deltaTime;
    if (positionX < 0) positionX = 0.f;
    if (positionX + width >= Engine::Get().GetWidth()) positionX = static_cast<float>(Engine::Get().GetWidth() - width);
    
    positionY += directionY * moveSpeed * deltaTime;
    if (positionY < 0) positionY = 0.f;
    
    // 새로운 위치로 업데이트
    Vector2 newPosition = GetPosition();
    newPosition.x = static_cast<int>(positionX);
    newPosition.y = static_cast<int>(positionY);
    SetPosition(newPosition);
    
}

