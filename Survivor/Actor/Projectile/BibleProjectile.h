#pragma once
#include <string>
#include <Math/Vector2.h>

#include "ProjectileBase.h"

class BibleProjectile  : public ProjectileBase
{
    TYPE_DECLARATIONS(BibleProjectile, ProjectileBase)
    
public:
    BibleProjectile(const Craft::Vector2& position, 
        const std::string& image, 
        Craft::Color color, 
        const float directionX, 
        const float directionY);
    
    ~BibleProjectile() = default;
    
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;
    
    void SetBibleIndex(int index) { this->bibleIndex = index; }
    
protected:
    virtual void Tick(float deltaTime) override;
    
    
/* Movement+ */    
protected:
    virtual void Move(float targetDirectionX, float targetDirectionY, float deltaTime) override;
    
private:
    float angle = 0.f;
    float radius = 10.f;
    float angularSpeed = 2.f;            
    
    int bibleIndex = 0; 
};
