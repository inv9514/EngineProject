#include "WeaponBase.h"
#include <Component/RelativeSpriteRendererComponent.h>
#include <Level/Level.h>

#include "Actor/Projectile/KnifeProjectile.h"
#include "Actor/Projectile/ProjectileBase.h"

using namespace Craft;

WeaponBase::WeaponBase(const Vector2& position)
    : Actor(position)
{
    fireTimer.SetTargetTime(fireInterval);
}


void WeaponBase::ShotProjectile(const float directionX, const float directionY)
{
    if (!CanShot()) return;
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    level->SpawnActor<KnifeProjectile>(GetWorldPosition(), "o", Color::White, directionX, directionY);
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
