#pragma once
#include "WeaponBase.h"

class HolyWater : public WeaponBase
{
    TYPE_DECLARATIONS(HolyWater,WeaponBase)

public:
    using WeaponBase::WeaponBase;
    
    void ShotProjectile(const float directionX, const float directionY) override;
    
};
