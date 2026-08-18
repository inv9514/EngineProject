#pragma once

#include <Level/Level.h>

class GameOverLevel : public Craft::Level
{
    TYPE_DECLARATIONS(GameOverLevel, Level)
public:
    virtual void Tick(float deltaTime) override;
    virtual void Draw() override;
};