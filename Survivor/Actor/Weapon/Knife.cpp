#include "Knife.h"
#include <Level/level.h>
#include <Actor/Projectile/KnifeProjectile.h>

using namespace Craft;

void Knife::ShotProjectile(const float directionX, const float directionY)
{
    if (!CanShot()) return;
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    level->SpawnActor<KnifeProjectile>(GetWorldPosition(), "*", Color::White, directionX, directionY);
}
