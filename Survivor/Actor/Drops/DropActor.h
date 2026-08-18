#pragma once
#include <Actor/Actor.h>

class DropActor : public Craft::Actor
{
    TYPE_DECLARATIONS(DropActor, Actor)
    
public:
    DropActor(const Craft::Vector2& position);

    void OnCollision(const std::shared_ptr<Craft::Actor>& other) override;

    
private:
    int expAmount = 10;
};
