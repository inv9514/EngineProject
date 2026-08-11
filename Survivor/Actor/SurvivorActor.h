#pragma once
#include <Actor/Actor.h>

class SurvivorActor : public Craft::Actor
{
    TYPE_DECLARATIONS(SurvivorActor, Actor);
    
public:
    SurvivorActor(const std::string& image, const Craft::Vector2& position, Craft::Color color)
    : Actor(image, position, color)
    {
    }
    
    virtual void Draw() override;
        
};
