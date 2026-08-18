#pragma once
#include <Actor/Actor.h>
#include <Util/Timer.h>
#include "Actor/Weapon/WeaponBase.h"

class RelativeSpriteRendererComponent;

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
    float damage = 0.2f;
    
/* Position */    
protected:      
    float positionX = 0.f;    
    float positionY = 0.f;
    
/* Life Span */    
protected:
    float lifeSpan = 3.f;     
    
    Timer lifeSpanTimer;
    
/* Visual */
    Timer colorTimer;
    
    int colorIndex = 0;
    
    std::shared_ptr<RelativeSpriteRendererComponent> spriteRendererComponent;
    
};
