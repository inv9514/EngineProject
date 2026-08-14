#pragma once
#include "ProjectileBase.h"


class KnifeProjectile : public ProjectileBase
{
    TYPE_DECLARATIONS(KnifeProjectile, ProjectileBase)
    
public:
    KnifeProjectile(const Craft::Vector2& position,
        const std::string& image, 
        Craft::Color color, 
        const float directionX, 
        const float directionY);
    
    ~KnifeProjectile() = default;
    
private:
    std::string GetImage(const float& directionX, const float& directionY);
};
