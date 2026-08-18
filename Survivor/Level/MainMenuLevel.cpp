#include "MainMenuLevel.h"

#include "Game/Game.h"
#include <Engine/Engine.h>
#include <Input/Input.h>
#include <Render/Renderer.h>

using namespace Craft;


MainMenuLevel::MainMenuLevel()
{
    itemList.emplace_back(
        std::make_unique<MenuItem>(
            "Game Start",
            []()
            {
                Game& game = dynamic_cast<Game&>(Engine::Get());
                game.OpenGameLevel();
            }
        )
    );

    itemList.emplace_back(
        std::make_unique<MenuItem>(
            "Quit Game",
            []()
            {
                Engine::Get().Quit();
            }
        )
    );
}

void MainMenuLevel::Tick(float deltaTime)
{
    Level::Tick(deltaTime);
    
    const int length = static_cast<int>(itemList.size());

    if (Input::Get().GetKeyDown(VK_UP))
    {
        currentIndex = (currentIndex - 1 + length) % length;
    }

    if (Input::Get().GetKeyDown(VK_DOWN))
    {
        currentIndex = (currentIndex + 1) % length;
    }

    if (Input::Get().GetKeyDown(VK_RETURN))
    {
        itemList[currentIndex]->onSelected();
    }
}

void MainMenuLevel::Draw()
{
    Level::Draw();
    Renderer::Get().Submit("Vampire Survivor",Vector2(66, 3),Color::BrightRed);

    const int count = static_cast<int>(itemList.size());

    for (int ix = 0; ix < count; ++ix)
    {
        Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor;
        Renderer::Get().Submit(itemList[ix]->text, Vector2(68, 6 + ix),textColor);
    }
}
