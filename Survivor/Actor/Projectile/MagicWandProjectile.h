#pragma once
#include "ProjectileBase.h"

class MagicWandProjectile: public ProjectileBase
{
    TYPE_DECLARATIONS(MagicWandProjectile, ProjectileBase)
    
public:
    using ProjectileBase::ProjectileBase;
    
    ~MagicWandProjectile() = default;
    
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;    
    
/* 누적 Damage */
public:
    static float GetTotalDamage() {  return totalDamage; }

private:
    static float totalDamage;
};
