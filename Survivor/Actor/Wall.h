#pragma once
#include <Actor/Actor.h>

#include "SurvivorActor.h"

class Wall : public Craft::Actor
{
    TYPE_DECLARATIONS(Wall , Actor)
    
public:
    Wall(const Craft::Vector2& position);    
    
    virtual void Draw() override;
    
private:
};
