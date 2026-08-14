#pragma once
#include "ProjectileBase.h"

class MagicWandProjectile: public ProjectileBase
{
    TYPE_DECLARATIONS(MagicWandProjectile, ProjectileBase)
    
public:
    MagicWandProjectile(const Craft::Vector2& position,
        const std::string& image, 
        Craft::Color color, 
        const float directionX, 
        const float directionY);
    
    ~MagicWandProjectile() = default;
    
    
};
