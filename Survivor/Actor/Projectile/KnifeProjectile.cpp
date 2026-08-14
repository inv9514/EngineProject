#include "KnifeProjectile.h"

using namespace Craft;


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
