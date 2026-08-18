#pragma once
#include <string>
#include <Actor/Actor.h>

#include "Util/Timer.h"
#include "Weapon/WeaponBase.h"

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
public:
    inline int GetCurrentLevel() { return playerLevel; }
    inline int GetCurrentExp() { return exp; }
    inline int GetCurrentRequiredExp() { return GetRequiredExp(); }
    
    inline float GetPlayerLife() { return playerLife; }
    
private:
    float playerLife = 100.f;
    float maxMoveSpeed = 25.f;
    float moveSpeed = 25.0f;   
    
    int playerLevel = 1;
    int exp = 0;
    
/* Combat */
public: 
    void TakeDamage(const float damage);
    
private:
    void FlashHitEffect(const Craft::Color& color);
    
private:    
    Timer reactionTimer;
    
    float reactionDuration = 0.4f; 
    
    Craft::Vector2 knockBackDirection;
    
    float knockBackSpeed = 15.f;
    
    std::shared_ptr<RelativeSpriteRendererComponent> spriteRendererComponent;
    
/* Weapon Section */
public:
    inline const std::vector<std::shared_ptr<WeaponBase>>& GetWeaponList() { return weaponList; }
    
private:
    void Fire();
    
private:
    std::vector<std::shared_ptr<WeaponBase>> weaponList;    

/* Exp */
public:
    void ReceiveExp(int expAmount);
    
private:
    const int GetRequiredExp();    
    
/* Upgrade */    
public:
    void UpgradeWeapon(WeaponType weaponType);
    
    int GetWeaponLevel(WeaponType type) const;
};
