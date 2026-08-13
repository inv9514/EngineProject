#pragma once
#include <Component/Component.h>

// AttributeSet처럼 쓰려고했는데 쓸만한 멤버가 두개밖에 없어서 일단 롤백 

class StatusComponent : public Craft::Component
{
    TYPE_DECLARATIONS(StatusComponent, Component)
public:
    StatusComponent(const float& inHealth, const float& inMoveSpeed)
        : maxHealth(inHealth), health(inHealth), moveSpeed(inMoveSpeed)
    {
        
    }
    
    ~StatusComponent() = default;
    
/* Event */
    virtual void Tick(float DeltaTime) override;
    
/* Status 접근 */    
public:   
    inline void SetMaxHealth(const float& inMaxHealth) { maxHealth = inMaxHealth; }
    inline float GetMaxHealth() const { return maxHealth; }
    
    inline void SetHealth(const float& inHealth) { health = inHealth; }
    inline float GetHealth() const { return health; }
    
    inline void SetMoveSpeed(const float& inMoveSpeed) { moveSpeed = inMoveSpeed; }       
    inline float GetMoveSpeed() const { return moveSpeed; }
    
    void TakeDamage(float inDamage);    
        
private:
    float maxHealth;
    float health;    
    float moveSpeed;                       
};
