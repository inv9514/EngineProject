#include "Game.h"

#include "Level/GameLevel.h"
#include "Level/GameOverLevel.h"
#include "Level/MainMenuLevel.h"
#include "Level/PauseLevel.h"
#include "Level/SelectLevel.h"


Game::Game()
{
    // TODO : 진짜쓰레기같은코드인데방법이없다
    std::shared_ptr<GameLevel> gameLevel = std::make_shared<GameLevel>();
    std::shared_ptr<SelectLevel> selectLevel = std::make_shared<SelectLevel>();

    gameLevel->SetSelectLevel(selectLevel);

    levelList.emplace_back(gameLevel);
    levelList.emplace_back(std::make_shared<MainMenuLevel>());
    levelList.emplace_back(std::make_shared<PauseLevel>());
    levelList.emplace_back(selectLevel);
    levelList.emplace_back(std::make_shared<GameOverLevel>());

    currentLevelState = LevelState::MainMenu;
    mainLevel = levelList[static_cast<int>(currentLevelState)];
}

void Game::OpenMainMenu()
{
}

void Game::OpenGameLevel()
{
    currentLevelState = LevelState::GameLevel;
    mainLevel = levelList[static_cast<int>(currentLevelState)];
}

void Game::OpenPauseMenu()
{
    currentLevelState = LevelState::PauseLevel;
    mainLevel = levelList[static_cast<int>(currentLevelState)];
}

void Game::OpenSelectMenu()
{
    currentLevelState = LevelState::SelectLevel;
    mainLevel = levelList[static_cast<int>(currentLevelState)];
}

void Game::OpenGameOverLevel()
{
    currentLevelState = LevelState::GameOverLevel;
    mainLevel = levelList[static_cast<int>(currentLevelState)];
}
