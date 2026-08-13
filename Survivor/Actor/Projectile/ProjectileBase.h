#pragma once
#include <string>
#include <Actor/Actor.h>

#include "Util/Timer.h"

class ProjectileBase : public Craft::Actor
{
    TYPE_DECLARATIONS(ProjectileBase, Actor)

/* Event */    
public:
    ProjectileBase(const Craft::Vector2& position, const std::string& image, const float& directionX, const float& directionY);
    ~ProjectileBase() = default;
    
    virtual void Tick(float deltaTime) override;
    
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;
    
/* Projectile Stat */
    float damage = 5.f;
    
/* Movement */
private:
    void Move(float targetDirectionX, float targetDirectionY, float deltaTime);
    
private:
    float moveSpeed = 50.f;        
    float positionX = 0.f;    
    float positionY = 0.f;
    float directionX = 0.f;
    float directionY = 0.f;    
    
/* Life Span */    
private:
    float lifeSpan = 1.f;        
    
    Timer lifeSpanTimer;
};
