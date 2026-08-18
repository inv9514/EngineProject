#pragma once
#include "ProjectileBase.h"


class KnifeProjectile : public ProjectileBase
{
    TYPE_DECLARATIONS(KnifeProjectile, ProjectileBase)
    
public:
    using ProjectileBase::ProjectileBase;
    
    ~KnifeProjectile() = default;
    
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;    
    
/* 누적 Damage */
public:
    static float GetTotalDamage() {  return totalDamage; }

private:
    static float totalDamage;
};
