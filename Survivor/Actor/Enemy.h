#pragma once
#include <Actor/Actor.h>

class Enemy : public Craft::Actor
{
    TYPE_DECLARATIONS(Enemy, Actor)
public:
    Enemy();
    
private:
    virtual void BeginPlay() override;	
    virtual void Tick(float deltaTime) override;
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;

    void Move(float directionX, float directionY, float deltaTime);
    
private:		
    float positionX = 0.0f; 
    float positionY = 0.0f;
    float moveSpeed = 70.0f;
    
};
