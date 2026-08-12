#include "Enemy.h"
#include <Component/RelativeSpriteRendererComponent.h>
#include <Component/BoxCollisionComponent.h>

using namespace Craft;

Enemy::Enemy()
    : Actor(Vector2::Zero)
{
    // 컴포넌트 추가 
    AddComponent<RelativeSpriteRendererComponent>("E", Color::Green, 5);
    AddComponent<BoxCollisionComponent>(1);
	
    // 생성 위치 설정
    SetPosition(Vector2(0, 0));

    // 현재위치 저장 
    positionX = static_cast<float>(0);
    positionY = static_cast<float>(0);
}

void Enemy::BeginPlay()
{
    
}

void Enemy::Tick(float DeltaTime)
{
    
}

void Enemy::OnCollision(const std::shared_ptr<Actor>& other)
{
    
}

void Enemy::Move(float directionX, float directionY, float deltaTime)
{
    
}
