#pragma once
#include "WeaponBase.h"

class Bible : public WeaponBase
{
    TYPE_DECLARATIONS(Bible, WeaponBase)
    
public:
    Bible(const Craft::Vector2& position, int weaponLevel = 1);
    ~Bible() = default;  
    
    virtual void ShotProjectile(float directionX, float directionY) override;    
    
protected:
    /* Projectile Stat */
    float damage = 5.f;
    float knockBackForce = 4.f;
    
    /* Movement */
protected:
    void Move(float targetDirectionX, float targetDirectionY, float deltaTime);
    
protected:
    float moveSpeed = 100.f;        
    float positionX = 0.f;    
    float positionY = 0.f;
    float directionX = 0.f;
    float directionY = 0.f;  
    
private:
    float angle = 0.f;
    float radius = 10.f;
    float angularSpeed = 2.f;    
    
/* Upgrade */
public:
    virtual void ApplyLevelAdjustment() override;
    
private:
    int bibleCount = 1;
    bool isAlreadyExist = false;
    
    
};
