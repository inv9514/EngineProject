#include "Knife.h"
#include <Level/level.h>
#include <Actor/Projectile/KnifeProjectile.h>

using namespace Craft;

Knife::Knife(const Craft::Vector2& position)
    : super(position)
{
    weaponData.weaponLevel = 1;
    weaponData.damage = 5.f;
    weaponData.projectileSpeed = 60.f;
    weaponData.knockBackForce = 3.f;
    weaponData.fireInterval = 0.2f;
    
    cooldownTimer.SetTargetTime(weaponData.fireInterval);
}

void Knife::ShotProjectile(const float directionX, const float directionY)
{
    if (!CanShot()) return;
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
        
    level->SpawnActor<KnifeProjectile>
    (GetWorldPosition(), GetImage(directionX, directionY), Color::White, directionX, directionY, weaponData);
}

std::string Knife::GetImage(const float& directionX, const float& directionY)
{
    if (directionX > 0.f && directionY > 0.f) return "\\";    
    if (directionX > 0.f && directionY < 0.f) return "/";    
    if (directionX < 0.f && directionY < 0.f) return "\\";    
    if (directionX < 0.f && directionY > 0.f) return "/";
    if (directionX != 0.f && directionY == 0.f) return "-";
    if (directionX == 0.f && directionY != 0.f) return "|"; 
    
    return "|";    
}
