#pragma once
#include <Actor/Actor.h>
#include <Util/Timer.h>
#include "Actor/Weapon/WeaponBase.h"

class ExplosiveActor : public Craft::Actor
{
    TYPE_DECLARATIONS(ExplosiveActor, Actor)
    
/* Event */
public:
    ExplosiveActor(const Craft::Vector2& position);
    
    ~ExplosiveActor() = default;
    
    virtual void Tick(float deltaTime) override;
    
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;
    
/* Damage Stats*/    
protected:
    int weaponLevel = 1;
    float damage = 1.f;
    
/* Position */    
protected:      
    float positionX = 0.f;    
    float positionY = 0.f;
    
/* Life Span */    
protected:
    float lifeSpan = 0.3f;        
    
    Timer lifeSpanTimer;
};
