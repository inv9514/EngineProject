#include "HolyWater.h"
#include <Level/level.h>
#include <Actor/Projectile/HolyWaterProjectile.h>

#include <Util/Util.h>

using namespace Craft;

HolyWater::HolyWater(const Craft::Vector2& position)
    : super (position)
{
    weaponData.weaponLevel = 1;
    weaponData.damage = 0.f;
    weaponData.knockBackForce = 0.f;
    weaponData.projectileSpeed = 20.f;
    weaponData.fireInterval = 2.f;
    
    cooldownTimer.SetTargetTime(weaponData.fireInterval);
}

void HolyWater::ShotProjectile(const float directionX, const float directionY)
{
    if (!CanShot()) return;
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    float randomDirectionX = Util::RandomRange(-1.f, 1.f);
    float randomDirectionY = Util::RandomRange(-1.f, 1.f);
    
    level->SpawnActor<HolyWaterProjectile>
    (GetWorldPosition(), "&&", Color::Cyan, randomDirectionX, randomDirectionY, weaponData);
}
