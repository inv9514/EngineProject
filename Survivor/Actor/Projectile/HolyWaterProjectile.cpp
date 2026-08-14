#include "HolyWaterProjectile.h"

#include "../../../CraftEngine/Util/Util.h"

using namespace Craft;

HolyWaterProjectile::HolyWaterProjectile(
    const Vector2& position,
    const std::string& image, 
    Color color,
    const float directionX,
    const float directionY)
:  super(position, "&&", Color::Cyan, directionX, directionY)
{
    damage = 5.f;
    knockBackForce = 0.f;
    moveSpeed = 30.f;
    lifeSpan = Util::RandomRange(0.5f, 1.5f); 
}
