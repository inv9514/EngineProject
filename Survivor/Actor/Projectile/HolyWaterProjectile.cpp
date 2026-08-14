#include "HolyWaterProjectile.h"
#include <Component/Component.h>
#include <Level/Level.h>
#include <Util/Util.h>

using namespace Craft;

HolyWaterProjectile::HolyWaterProjectile(
    const Vector2& position,
    const std::string& image,
    Color color,
    float directionX,
    float directionY,
    const WeaponData& weaponData)
    : super(
        position,
        image,
        color,
        directionX,
        directionY,
        weaponData)
{    
    lifeSpanTimer.SetTargetTime(Util::RandomRange(0.5f, 1.5f));
}

void HolyWaterProjectile::Tick(float deltaTime)
{
    // Actor::Tick 이벤트
    if (!IsActive()) return;			
    for (const std::shared_ptr<Component>& component : componentList) component->Tick(deltaTime);
    
    Move(directionX, directionY, deltaTime);   
    
    lifeSpanTimer.Tick(deltaTime);
    if (lifeSpanTimer.IsTimeOut())
    {
        // 폭발시작 
        Destroy();
    }
}
