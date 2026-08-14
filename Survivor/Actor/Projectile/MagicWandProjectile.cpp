#include "MagicWandProjectile.h"
#include <iostream>

using namespace Craft; 

MagicWandProjectile::MagicWandProjectile(const Craft::Vector2& position,
    const std::string& image,
    Color color, 
    const float directionX,
    const float directionY)
    : super(position, "*", Color::BrightPurple, directionX, directionY)
{
    damage = 5.f;
    knockBackForce = 2.f;
    moveSpeed = 30.f;
}
