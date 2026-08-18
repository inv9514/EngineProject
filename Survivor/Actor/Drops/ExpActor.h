#pragma once
#include <Actor/Actor.h>


class ExpActor : public Craft::Actor
{
    TYPE_DECLARATIONS(ExpActor, Actor)
public:
    ExpActor(const Craft::Vector2& position);

    void OnCollision(const std::shared_ptr<Craft::Actor>& other) override;

    
private:
    int expAmount = 10;
};