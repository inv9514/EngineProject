#include "Bullet.h"

Bullet::Bullet(const Craft::Vector2& position, const std::string& image, const float& directionX, const float& directionY)
    : super(position, GetImage(directionX, directionY), directionX, directionY)
{
    
}

std::string Bullet::GetImage(const float& directionX, const float& directionY)
{
    if (directionX > 0.f && directionY > 0.f) return "\\";    
    if (directionX > 0.f && directionY < 0.f) return "/";    
    if (directionX < 0.f && directionY < 0.f) return "\\";    
    if (directionX < 0.f && directionY > 0.f) return "/";
    if (directionX != 0.f && directionY == 0.f) return "-";
    if (directionX == 0.f && directionY != 0.f) return "|"; 
    
    return "|";
    
}
