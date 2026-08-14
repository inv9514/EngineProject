#include "KnifeProjectile.h"

using namespace Craft;

KnifeProjectile::KnifeProjectile(const Craft::Vector2& position,
    const std::string& image,
    Color color, 
    const float directionX,
    const float directionY)
    : super(position, GetImage(directionX, directionY), Color::White, directionX, directionY)
{
    damage = 5.f;
    knockBackForce = 2.f;
    moveSpeed = 60.f;
}

std::string KnifeProjectile::GetImage(const float& directionX, const float& directionY)
{
    if (directionX > 0.f && directionY > 0.f) return "\\";    
    if (directionX > 0.f && directionY < 0.f) return "/";    
    if (directionX < 0.f && directionY < 0.f) return "\\";    
    if (directionX < 0.f && directionY > 0.f) return "/";
    if (directionX != 0.f && directionY == 0.f) return "-";
    if (directionX == 0.f && directionY != 0.f) return "|"; 
    
    return "|";
    
}
