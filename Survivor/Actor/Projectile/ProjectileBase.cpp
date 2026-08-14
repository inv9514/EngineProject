
#include "ProjectileBase.h"

#include <Component/RelativeSpriteRendererComponent.h>
#include <Component/BoxCollisionComponent.h>
#include "Actor/Enemy.h"

using namespace Craft;

ProjectileBase::ProjectileBase    // Weapon에서 Projectile 생성시 위치, 이미지, 색, 방향, 스탯을 지정해 생성
    (const Vector2& position,
    const std::string& image, 
    Color color,
    const float directionX, 
    const float directionY,
    const WeaponData& weaponData)

    : super(position), 
    positionX(static_cast<float>(position.x)), 
    positionY(static_cast<float>(position.y)),
    directionX(directionX),
    directionY(directionY)    
{
    AddComponent<RelativeSpriteRendererComponent>(image, color, 5);
    AddComponent<BoxCollisionComponent>(1);
    
    weaponLevel = weaponData.weaponLevel;
    damage = weaponData.damage;
    knockBackForce = weaponData.knockBackForce;
    moveSpeed = weaponData.projectileSpeed;
    
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
    super::OnCollision(other);
    
    if (other->IsTypeOf<Enemy>())
    {
        std::shared_ptr<Enemy> enemy = Cast<Enemy>(other);
        if (!enemy) return;
        
        Vector2 knockBack = Vector2(
            static_cast<int>(directionX * knockBackForce * -1),
            static_cast<int>(directionY * knockBackForce * -1));
        
        HitStruct hitStruct(damage, knockBack);
       
        enemy->ReceiveHitStruct(hitStruct);        
        Destroy();
    }
        
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