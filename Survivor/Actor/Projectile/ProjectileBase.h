#pragma once
#include <string>
#include <Actor/Actor.h>

#include "Util/Timer.h"

class ProjectileBase : public Craft::Actor
{
    TYPE_DECLARATIONS(ProjectileBase, Actor)

/* Event */    
public:
    ProjectileBase(const Craft::Vector2& position, 
        const std::string& image, 
        Craft::Color color,  
        const float directionX, 
        const float directionY);
    
    ~ProjectileBase() = default;
    
    virtual void Tick(float deltaTime) override;
    
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;    
        
    
/* Projectile Stat */
protected:
    float damage = 1.f;
    float knockBackForce = 1.f;
    float moveSpeed = 50.f;  
    
/* Movement */
protected:
    virtual void Move(float targetDirectionX, float targetDirectionY, float deltaTime);
    
protected:      
    float positionX = 0.f;    
    float positionY = 0.f;
    float directionX = 0.f;
    float directionY = 0.f;  
    
/* Life Span */    
protected:
    float lifeSpan = 3.f;        
    
    Timer lifeSpanTimer;
};
