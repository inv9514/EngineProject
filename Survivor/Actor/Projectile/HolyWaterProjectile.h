#pragma once
#include "ProjectileBase.h"

class HolyWaterProjectile : public ProjectileBase
{
    TYPE_DECLARATIONS(HolyWaterProjectile, ProjectileBase)

public:
    HolyWaterProjectile(const Craft::Vector2& position, 
        const std::string& image, 
        Craft::Color color, 
        const float directionX, 
        const float directionY);
    
    ~HolyWaterProjectile() = default;
    
};
