#pragma once
#include <functional>
#include <string>
#include <Level/Level.h>

struct MenuItem
{
    MenuItem(const std::string& text, std::function<void()> onSelected)
        : text(text), onSelected(std::move(onSelected))
    {
    }

    std::string text;
    std::function<void()> onSelected;
};

class MainMenuLevel : public Craft::Level
{
    TYPE_DECLARATIONS(MainMenuLevel, Level)

public:
    MainMenuLevel();

    void Tick(float deltaTime) override;
    void Draw() override;

private:
    std::vector<std::unique_ptr<MenuItem>> itemList;

    int currentIndex = 0;

    Craft::Color selectedColor = Craft::Color::White;
    Craft::Color unselectedColor = Craft::Color::Gray;
    
};
