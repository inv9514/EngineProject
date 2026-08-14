#pragma once
#include "ProjectileBase.h"

class MagicWandProjectile: public ProjectileBase
{
    TYPE_DECLARATIONS(MagicWandProjectile, ProjectileBase)
    
public:
    using ProjectileBase::ProjectileBase;
    
    ~MagicWandProjectile() = default;
    
    
};
