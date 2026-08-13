#include "ProjectileBase.h"

#include <Component/RelativeSpriteRendererComponent.h>
#include <Component/BoxCollisionComponent.h>

#include "Actor/Enemy.h"

using namespace Craft;

ProjectileBase::ProjectileBase(const Vector2& position, const std::string& image,  const float& directionX, const float& directionY)
    : super(position), 
    positionX(static_cast<float>(position.x)), 
    positionY(static_cast<float>(position.y)),
    directionX(directionX),
    directionY(directionY)
{
    AddComponent<RelativeSpriteRendererComponent>(image, Color::White, 1);
    AddComponent<BoxCollisionComponent>(1);
    
    lifeSpanTimer.SetTargetTime(lifeSpan);
}

void ProjectileBase::Tick(float deltaTime)
{
    super::Tick(deltaTime);
    
    Move(directionX, directionY, deltaTime);   
    
    lifeSpanTimer.Tick(deltaTime);
    if (lifeSpanTimer.IsTimeOut()) Destroy(); // 수명 종료시 액터 파괴
}

void ProjectileBase::OnCollision(const std::shared_ptr<Actor>& other)
{
    Actor::OnCollision(other);
    
    if (other->IsTypeOf<Enemy>()) Destroy();
}

void ProjectileBase::Move(float targetDirectionX, float targetDirectionY, float deltaTime)
{    
    positionX += targetDirectionX * moveSpeed * deltaTime;    
    positionY += targetDirectionY * moveSpeed * deltaTime;
    
    Vector2 newPosition;
    newPosition.x = static_cast<int>(positionX);
    newPosition.y = static_cast<int>(positionY);
    
    SetPosition(newPosition);
}

