#pragma once
#include "WeaponBase.h"

class MagicWand : public WeaponBase
{
    TYPE_DECLARATIONS(MagicWand, WeaponBase)
    
public:
    MagicWand(const Craft::Vector2& position);    
    
    void ShotProjectile(const float directionX, const float directionY) override;
    
    virtual void ApplyLevelAdjustment();
};
