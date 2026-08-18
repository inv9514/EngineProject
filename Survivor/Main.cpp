
#include <Engine/Engine.h>
#include <Level/GameLevel.h>

#include "Game/Game.h"
#include "Level/MainMenuLevel.h"

int main()
{
    Game game;
    game.AddNewLevel<MainMenuLevel>();
    game.Run();
}
