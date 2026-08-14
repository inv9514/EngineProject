#include "HolyWater.h"
#include <Level/level.h>
#include <Actor/Projectile/HolyWaterProjectile.h>

#include "../../../CraftEngine/Util/Util.h"

using namespace Craft;

void HolyWater::ShotProjectile(const float directionX, const float directionY)
{
    if (!CanShot()) return;
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    float randomDirectionX = Util::RandomRange(-1.f, 1.f);
    float randomDirectionY = Util::RandomRange(-1.f, 1.f);
    
    level->SpawnActor<HolyWaterProjectile>(GetWorldPosition(), "&&", Color::Cyan, randomDirectionX, randomDirectionY);

}
