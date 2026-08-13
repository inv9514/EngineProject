#include "WeaponBase.h"
#include <Component/RelativeSpriteRendererComponent.h>
#include <Level/Level.h>

#include "Actor/Projectile/Bullet.h"
#include "Actor/Projectile/ProjectileBase.h"

using namespace Craft;

WeaponBase::WeaponBase(const Vector2& position)
    : Actor(position)
{
    fireTimer.SetTargetTime(fireInterval);
}


void WeaponBase::ShotProjectile(const float& directionX, const float& directionY)
{
    if (!CanShot()) return;
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    level->SpawnActor<Bullet>(GetWorldPosition(), "*", directionX, directionY);
}

void WeaponBase::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
    
    fireTimer.Tick(deltaTime);
}

bool WeaponBase::CanShot()
{
    if (!fireTimer.IsTimeOut()) return false;
    
    fireTimer.Reset();
    return true;
}
