#pragma once
#include <Actor/Actor.h>

class Player : public Craft::Actor
{
    TYPE_DECLARATIONS(Player, Actor)
    
public:
    Player();
    
private:          
    virtual void Tick(float deltaTime) override;
    
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;
    
    void Move(float directionX, float directionY, float deltaTime);
    
    
private:
    float positionX = 0.f;
    
    float positionY = 0.f;
    
    float moveSpeed = 30.f;        
    
};
