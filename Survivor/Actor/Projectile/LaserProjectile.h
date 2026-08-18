#pragma once
#include "ProjectileBase.h"

class RelativeSpriteRendererComponent;

class LaserProjectile : public ProjectileBase
{
    TYPE_DECLARATIONS(LaserProjectile, ProjectileBase)
    
public:
    LaserProjectile(
    const Craft::Vector2& position,
    const std::string& image,
    Craft::Color color,
    float directionX,
    float directionY,
    const WeaponData& weaponData);

    void Tick(float deltaTime) override;
    void OnCollision(const std::shared_ptr<Craft::Actor>& other) override;

/* Visual */
private:
    Timer colorTimer;
    
    int colorIndex = 0;
    
    std::shared_ptr<RelativeSpriteRendererComponent> spriteRendererComponent;
    
/* 누적 Damage */
public:
    static float GetTotalDamage() {  return totalDamage; }

private:
    static float totalDamage;
};
