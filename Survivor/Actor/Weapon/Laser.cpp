#include "Laser.h"
#include <Level/level.h>
#include <Actor/Projectile/LaserProjectile.h>

using namespace Craft;

Laser::Laser(const Craft::Vector2& position)
    : super(position)
{
    weaponType = WeaponType::Laser;
    
    weaponData.weaponLevel = 1;
    weaponData.damage = 0.8f;
    weaponData.projectileSpeed = 0.f;  // 얜 즉발소환
    weaponData.knockBackForce = 0.f;
    weaponData.fireInterval = 2.f;
    
    cooldownTimer.SetTargetTime(weaponData.fireInterval);
}

void Laser::ShotProjectile(const float directionX, const float directionY)
{
    if (!CanShot()) return;
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    Vector2 startPosition = GetWorldPosition();
    
        
    for (int i = 1; i <= laserLength; ++i)
    {
        Vector2 spawnPosition(
            startPosition.x + static_cast<int>(directionX * i),
            startPosition.y + static_cast<int>(directionY * i)
        );

        level->SpawnActor<LaserProjectile>(
            spawnPosition,
            GetImage(directionX, directionY),
            Color::BrightBlue,
            directionX,
            directionY,
            weaponData
        );
    }
}

void Laser::ApplyLevelAdjustment()
{
    weaponData.damage = 0.8f * (1.f + 0.05f * static_cast<int>(weaponData.weaponLevel - 1));
}

std::string Laser::GetImage(const float& directionX, const float& directionY)
{
    if (directionX > 0.f && directionY > 0.f) return "\\";    
    if (directionX > 0.f && directionY < 0.f) return "/";    
    if (directionX < 0.f && directionY < 0.f) return "\\";    
    if (directionX < 0.f && directionY > 0.f) return "/";
    if (directionX != 0.f && directionY == 0.f) return "-";
    if (directionX == 0.f && directionY != 0.f) return "|"; 
    
    return "|";    
}
