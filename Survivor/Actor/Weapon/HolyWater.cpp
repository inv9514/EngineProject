#include "HolyWater.h"
#include <Level/level.h>
#include <Actor/Projectile/HolyWaterProjectile.h>

#include <Util/Util.h>
#include <algorithm>
using namespace Craft;

HolyWater::HolyWater(const Craft::Vector2& position)
    : super (position)
{
    weaponType = WeaponType::HolyWater;
    
    weaponData.weaponLevel = 1;
    weaponData.damage = 0.f;
    weaponData.knockBackForce = 0.f;
    weaponData.projectileSpeed = 20.f;
    weaponData.fireInterval = 3.f;
    
    cooldownTimer.SetTargetTime(weaponData.fireInterval);
}

void HolyWater::ShotProjectile(const float directionX, const float directionY)
{
    if (!CanShot()) return;
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    for (int i = 0; i < waterProjectileCount; ++i)
    {
        float randomDirectionX = Util::RandomRange(-1.f, 1.f);
        float randomDirectionY = Util::RandomRange(-1.f, 1.f);
    
        level->SpawnActor<HolyWaterProjectile>
        (GetWorldPosition(), "&&", Color::Cyan, randomDirectionX, randomDirectionY, weaponData);
    }        
}

void HolyWater::ApplyLevelAdjustment()
{
    weaponData.damage = 7.f * (1.f + 0.05f * static_cast<int>(weaponData.weaponLevel - 1));    
    
    waterProjectileCount = min(1 + (weaponData.weaponLevel - 1) / 2, 4);
    
}