#pragma once
#include "WeaponBase.h"

class HolyWater : public WeaponBase
{
    TYPE_DECLARATIONS(HolyWater,WeaponBase)

public:
    HolyWater(const Craft::Vector2& position);
    
    void ShotProjectile(const float directionX, const float directionY) override;
    
    virtual void ApplyLevelAdjustment() override;
  
private:
    int waterProjectileCount = 1;
    
};
