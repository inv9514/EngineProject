#pragma once
#include <Component/Component.h>

class StatusComponent : public Craft::Component
{
    TYPE_DECLARATIONS(StatusComponent, Component)
public:
    StatusComponent(const float& inHealth, const float& inMoveSpeed)
        : health(inHealth), moveSpeed(inMoveSpeed)
    {
        
    }
    
    ~StatusComponent() = default;
    
/* Status 접근 */    
public:
    inline void SetHealth(const float& inHealth) { health = inHealth; }
    inline void SetMoveSpeed(const float& inMoveSpeed) { moveSpeed = inMoveSpeed; }
    
    inline float GetHealth() const { return health; }
    inline float GetMoveSpeed() const { return moveSpeed; }
    
private:
    float health;    
    float moveSpeed;           
    

    
    
};
