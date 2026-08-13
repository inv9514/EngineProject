#pragma once
#include <Actor/Actor.h>

class WeaponBase;

class Player : public Craft::Actor
{
    TYPE_DECLARATIONS(Player, Actor)
    
public:
    Player();
    
private:
    virtual void BeginPlay() override;	
    virtual void Tick(float deltaTime) override;
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;

    void Move(float directionX, float directionY, float deltaTime);
    void ProcessInput(float deltaTime);
    
private:		
    float positionX = 0.0f;
    float positionY = 0.0f;
    float directionX = 1.0f;  
    float directionY = 0.0f;
    float moveSpeed = 25.0f;
    
/* Weapon Section */
private:
    void Fire();
    
private:
    std::vector<std::shared_ptr<WeaponBase>> weaponList;   
            

};
