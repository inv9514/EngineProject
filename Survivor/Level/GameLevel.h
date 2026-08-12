#pragma once
#include <Level/Level.h>

#include "Actor/Player.h"

class GameLevel : public Craft::Level
{
    TYPE_DECLARATIONS(GameLevel, Level)
public:
    GameLevel() = default;
    ~GameLevel() = default;
    
private:
    virtual void OnInitialized() override;
    virtual void Tick(float deltaTime) override;
    virtual void Draw() override;
    
    std::shared_ptr<Craft::Actor> playerActor;
};
