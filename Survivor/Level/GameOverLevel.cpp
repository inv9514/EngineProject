#include "GameOverLevel.h"

#include <Engine/Engine.h>
#include <Input/Input.h>
#include <Render/Renderer.h>
#include "Game/Game.h"


using namespace Craft;

void GameOverLevel::Tick(float deltaTime)
{
    Level::Tick(deltaTime);

    if (Input::Get().GetKeyDown(VK_RETURN))
    {
        Game& game = dynamic_cast<Game&>(Engine::Get());
        game.Quit();
    }
}

void GameOverLevel::Draw()
{
    Level::Draw();

    Renderer::Get().Submit(
        "GAME OVER",
        Vector2(68, 18),
        Color::BrightRed,
        10);

    Renderer::Get().Submit(
        "Press Enter",
        Vector2(67, 22),
        Color::White,
        10);
}