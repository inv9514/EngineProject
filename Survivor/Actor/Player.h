#pragma once
#include <Actor/Actor.h>

#include "Util/Timer.h"

class RelativeSpriteRendererComponent;
class WeaponBase;

class Player : public Craft::Actor
{
    TYPE_DECLARATIONS(Player, Actor)
    
public:
    Player();
    
/* Event */    
private:
    virtual void BeginPlay() override;	
    virtual void Tick(float deltaTime) override;
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;

    void ProcessInput(float deltaTime);
    void Move(float directionX, float directionY, float deltaTime);
    
/* Position */
    
private:		
    float positionX = 0.0f;
    float positionY = 0.0f;
    float directionX = 1.0f;  
    float directionY = 0.0f;
    
/* Stats */
    float maxHp = 10.f;
    float currentHp = 10.f;
    float maxMoveSpeed = 25.f;
    float moveSpeed = 25.0f;
    
/* Combat */
public:
    void TakeDamage(const float& damage);
    
private:
    void FlashHitEffect(const Craft::Color& color);
    
private:    
    Timer reactionTimer;
    
    float reactionDuration = 0.4f; 
    
    Craft::Vector2 knockBackDirection;
    
    float knockBackSpeed = 15.f;
    
    std::shared_ptr<RelativeSpriteRendererComponent> spriteRendererComponent;
    
/* Weapon Section */
private:
    void Fire();
    
private:
    std::vector<std::shared_ptr<WeaponBase>> weaponList;               

};
