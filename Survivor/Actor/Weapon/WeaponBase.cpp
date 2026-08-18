#include "WeaponBase.h"
#include <Component/RelativeSpriteRendererComponent.h>
#include <Level/Level.h>

#include "Actor/Projectile/KnifeProjectile.h"
#include "Actor/Projectile/ProjectileBase.h"

using namespace Craft;

WeaponBase::WeaponBase(const Vector2& position)
    : Actor(position)
{    
    weaponData.weaponLevel = 1;
    weaponData.damage = 1.f;
    weaponData.projectileSpeed = 1.f;
    weaponData.knockBackForce = 1.f;
    weaponData.fireInterval = 1.f;
    
    cooldownTimer.SetTargetTime(weaponData.fireInterval);
}


void WeaponBase::ShotProjectile(float directionX, float directionY)
{
    if (!CanShot()) return;
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    level->SpawnActor<KnifeProjectile>
    (GetWorldPosition(), "o", Color::White, directionX, directionY, weaponData);
}

void WeaponBase::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
    
    cooldownTimer.Tick(deltaTime);
}

bool WeaponBase::CanShot()
{
    if (!cooldownTimer.IsTimeOut()) return false;
    
    cooldownTimer.Reset();
    return true;
}

void WeaponBase::ApplyLevelAdjustment()
{
    weaponData.damage = 4.f * (1.f + 0.05f * static_cast<int>(weaponData.weaponLevel - 1));  // 공증 5%
}