#pragma once
#include <string>

#include "WeaponBase.h"

class Laser : public WeaponBase
{
    TYPE_DECLARATIONS(Laser, WeaponBase)

public:
    Laser(const Craft::Vector2& position);
    
    void ShotProjectile(const float directionX, const float directionY) override;
    
    virtual void ApplyLevelAdjustment();
    
private:
    std::string GetImage(const float& directionX, const float& directionY);
    
    int laserLength = 80;
};
