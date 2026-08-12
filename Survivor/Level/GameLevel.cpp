#include "GameLevel.h"

#include <Actor/Player.h>
#include <Render/Renderer.h>

#include <Actor/Enemy.h>
#include <Engine/Engine.h>

using namespace Craft;


void GameLevel::OnInitialized()
{
    Level::OnInitialized();
    
    playerActor = SpawnActor<Player>();
    SetLevelCamera(std::make_shared<LevelCamera>(playerActor));
    SpawnActor<Enemy>();
}

void GameLevel::Tick(float deltaTime)
{
    Level::Tick(deltaTime);
}

void GameLevel::Draw()
{
    Level::Draw();
    
    for (int y = 0; y < Engine::Get().GetHeight(); ++y)
    {
        Renderer::Get().Submit("▒", Vector2(110, y));
    }
    
    std::shared_ptr<LevelCamera> camera = GetLevelCamera();
    if (!camera) return;
    
    Vector2 cameraPosition = camera->GetPosition();
    
    std::string position =
    "< " + std::to_string(static_cast<int>(cameraPosition.x)) + ", "
      +  std::to_string(static_cast<int>(cameraPosition.y)) +  " >";
    

    Renderer::Get().Submit("Player 위치", Vector2(117, 4));
    Renderer::Get().Submit(position, Vector2(117, 6));
}