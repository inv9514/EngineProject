#pragma once
#include <string>
#include <Actor/Actor.h>
#include <Util/Timer.h>

class ExplosiveSpawner : public Craft::Actor
{
    TYPE_DECLARATIONS(ExplosiveSpawner, Actor)    
    
/* Event */    
public:
    ExplosiveSpawner(const Craft::Vector2& position);
    ~ExplosiveSpawner() = default;
        
protected:
    void Tick(float deltaTime) override;    
 
public:
    virtual void CreateExplosiveActors();
};
