#pragma once
#include <Actor/Actor.h>
#include "Util/Timer.h"

class WeaponBase : public Craft::Actor
{
    TYPE_DECLARATIONS(WeaponBase, Actor)
    
public:
    WeaponBase(const Craft::Vector2& position);
    ~WeaponBase() = default;    
    
    void ShotProjectile(const float& directionX, const float& directionY);
    
protected:
    virtual void Tick(float deltaTime) override;
    
    bool CanShot();  
    
    float fireInterval = 0.2f; 
    
    Timer fireTimer;
};
