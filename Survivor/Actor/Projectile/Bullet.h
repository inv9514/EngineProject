#pragma once
#include "ProjectileBase.h"

class Bullet : public ProjectileBase
{
    TYPE_DECLARATIONS(Bullet, ProjectileBase)
    
public:
    Bullet(const Craft::Vector2& position, const std::string& image, const float& directionX, const float& directionY);
    ~Bullet() = default;
    
private:
    std::string GetImage(const float& directionX, const float& directionY);
};
