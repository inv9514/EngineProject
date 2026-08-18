#pragma once
#include "ProjectileBase.h"
#include "Actor/Explosive/ExplosiveSpawner.h"

class HolyWaterProjectile : public ProjectileBase
{
    TYPE_DECLARATIONS(HolyWaterProjectile, ProjectileBase)

public:
    HolyWaterProjectile(
        const Craft::Vector2& position,
        const std::string& image,
        Craft::Color color,
        float directionX,
        float directionY,
        const WeaponData& weaponData);
    
    ~HolyWaterProjectile() = default;
    
    void Tick(float deltaTime) override;
    
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;    
    
private:
    std::shared_ptr<ExplosiveSpawner> damageField;
    
/* 누적 Damage */
public:
    static float GetTotalDamage() {  return totalDamage; }

public:
    static float totalDamage;
    
};
