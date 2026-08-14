#pragma once
#include <string>

#include "WeaponBase.h"

class Knife : public WeaponBase
{
    TYPE_DECLARATIONS(Knife, WeaponBase)

public:
    Knife(const Craft::Vector2& position);
    
    void ShotProjectile(const float directionX, const float directionY) override;
    
private:
    std::string GetImage(const float& directionX, const float& directionY);
};
