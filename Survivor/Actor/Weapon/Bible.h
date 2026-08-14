#pragma once
#include "WeaponBase.h"

class Bible : public WeaponBase
{
    TYPE_DECLARATIONS(Bible, WeaponBase)
    
public:
    Bible(const Craft::Vector2& position);
    ~Bible() = default;  
    
    virtual void ShotProjectile(const float directionX, const float directionY) override;    
    
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
    
    /* Life Span */    
protected:    
    bool isAlreadyExist = false; // 나중에 웨폰레벨과 비교해서 < 으로 변경
    
};
