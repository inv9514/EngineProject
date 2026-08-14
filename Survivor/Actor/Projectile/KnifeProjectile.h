#pragma once
#include "ProjectileBase.h"


class KnifeProjectile : public ProjectileBase
{
    TYPE_DECLARATIONS(KnifeProjectile, ProjectileBase)
    
public:
    using ProjectileBase::ProjectileBase;
    
    ~KnifeProjectile() = default;
    
private:
    std::string GetImage(const float& directionX, const float& directionY);
};
