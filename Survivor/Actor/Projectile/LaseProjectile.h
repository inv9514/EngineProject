#pragma once
#include "ProjectileBase.h"

class LaseProjectile : public ProjectileBase
{
    TYPE_DECLARATIONS(LaseProjectile, ProjectileBase)
    
public:
    using ProjectileBase::ProjectileBase;
    
    ~LaseProjectile() = default;
    
private:
    std::string GetImage(const float& directionX, const float& directionY);
};
