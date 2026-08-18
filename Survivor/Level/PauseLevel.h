#pragma once

#include <functional>
#include <Level/Level.h>
#include <memory>
#include <string>
#include <vector>

#include "MainMenuLevel.h"

class PauseLevel : public Craft::Level
{
    TYPE_DECLARATIONS(PauseLevel, Level)

public:
    PauseLevel();

    void Tick(float deltaTime) override;
    void Draw() override;

private:
    std::vector<std::unique_ptr<MenuItem>> itemList;

    int currentIndex = 0;

    Craft::Color selectedColor = Craft::Color::White;
    Craft::Color unselectedColor = Craft::Color::Gray;
    
};
