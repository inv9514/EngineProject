#pragma once
#include <Actor/Actor.h>

class MagnetActor  : public Craft::Actor
{
    TYPE_DECLARATIONS(MagnetActor, Actor)
public:
    MagnetActor(const Craft::Vector2& position);

    void OnCollision(const std::shared_ptr<Craft::Actor>& other) override;
   
};