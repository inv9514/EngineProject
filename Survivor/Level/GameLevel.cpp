#include "GameLevel.h"

#include <algorithm>
#include <Render/Renderer.h>
#include <Engine/Engine.h>
#include <Math/Vector2.h>
#include <Actor/EnemySpawner.h>
#include <Actor/Player.h>

using namespace Craft;


void GameLevel::OnInitialized()
{
    Level::OnInitialized();
    
    // 플레이어 생성
    playerActor = SpawnActor<Player>();
    
    // LevelCamera 등록(추적 대상 : Player)
    SetLevelCamera(std::make_shared<LevelCamera>(playerActor));
    
    // EnemySpawner 생성
    OffScreenEnemySpawner();            
}

void GameLevel::Tick(float deltaTime)
{
    Level::Tick(deltaTime);    
    
    WaveControl(deltaTime);
}

void GameLevel::Draw()
{
    Level::Draw();
    
    // 구분선 내부는 다른액터가 보이지 않도록, 우선순위가 높은 공백값을 먼저 채우고
    // 아래는 그보다 우선순위가 높은 UI 글자들 배치
    
    // 구분선
    for (int y = 0; y < Engine::Get().GetHeight(); ++y)
    {
        Renderer::Get().Submit("▒                                    ", 
            Vector2(110, y), Color::White, 10);
    }
    
    // 플레이어 좌표 
    std::shared_ptr<LevelCamera> camera = GetLevelCamera();
    if (!camera) return;    
    Vector2 cameraPosition = camera->GetPosition();    
    std::string position =
    "< " + std::to_string(static_cast<int>(cameraPosition.x)) + ", "
      +  std::to_string(static_cast<int>(cameraPosition.y)) +  " >";   
    Renderer::Get().Submit("Player 위치", Vector2(117, 4), Color::White, 10);
    Renderer::Get().Submit(position, Vector2(117, 6), Color::White, 10);
    
    // Enemy Count
    Renderer::Get().Submit("Enemy Count", Vector2(117, 10), Color::White, 10);
    std::string enemyCount = std::to_string(static_cast<int>(Enemy::GetEnemyCount()));
    Renderer::Get().Submit(enemyCount, Vector2(117, 12), Color::White, 10);
   
    // Kill Count
    Renderer::Get().Submit("Kill Count", Vector2(117, 14), Color::White, 10);
    std::string killCount = std::to_string(static_cast<int>(Enemy::GetKillCount()));
    Renderer::Get().Submit(killCount, Vector2(117, 16), Color::White, 10);
    
    // 남은 시간
    
    // 라이프 
}

void GameLevel::WaveControl(float deltaTime)
{    
    if (!playerActor) return;
    Vector2 playerPosition = playerActor->GetWorldPosition();
    
    // 레벨의 모든 Enemy액터를 목록에 저장
    std::vector<std::shared_ptr<Enemy>> enemyList;
    for (const auto& actor : actorList)
    {
        std::shared_ptr<Enemy> enemy = Cast<Enemy>(actor);
        if (enemy) enemyList.push_back(enemy);
    }
    
    // 목록을 Player와 거리 가까운 순으로 재정렬
    std::sort(enemyList.begin(), enemyList.end(),
    [&](const std::shared_ptr<Enemy>& a, const std::shared_ptr<Enemy>& b)
    {
        Vector2 diffA = playerPosition - a->GetWorldPosition();
        Vector2 diffB = playerPosition - b->GetWorldPosition();
        int distSqA = diffA.x * diffA.x + diffA.y * diffA.y;
        int distSqB = diffB.x * diffB.x + diffB.y * diffB.y;
     
        return distSqA < distSqB; 
    });
    
    // Weapon::MagicWand 호밍기능을 위한 가장 가까운액터 체크
    if (enemyList.empty()) return;
    std::shared_ptr<Enemy>& nearestEnemy = enemyList[0];
    if (enemyList[0]) nearestEnemyPosition = enemyList[0]->GetWorldPosition();    
    
    // 가까운 액터부터 이동요청
    for (const auto& enemy : enemyList)
    {
        // Enemy에게서 요청받은 이동위치와 현재 위치
        Vector2 nextPosition = enemy->SubmitMoveRequest(playerPosition, deltaTime);
        Vector2 currentPosition = enemy->GetWorldPosition();

        // 둘을 비교해 움직이지 않을 액터들과 플레이어를 공격하는 위치의 액터는 이동 스킵
        if (nextPosition == currentPosition) continue;
        if (nextPosition == playerPosition)
        {
            // Enemy의 다음 위치가 Player일 경우 공격으로 판정
            
            continue;  
        }
            
        
        // 이동요청위치에 Enemy가 존재하는지 체크하고, 없다면 이동 허가처리
        if (IsPositionEmpty(nextPosition, enemy)) enemy->CommitMove(nextPosition);
        else enemy->MoveRejection();
    }
}

bool GameLevel::IsPositionEmpty(const Vector2& position, const std::shared_ptr<Enemy>& self)
{
    // 레벨의 모든 액터를 대상으로 특정위치에 Enemy가 존재하는지 체크
    for (const auto& actor : actorList)
    {
        std::shared_ptr<Enemy> enemy = Cast<Enemy>(actor);        
        if (!enemy || enemy == self) continue;                   // 본인은 제외 

        if (enemy->GetWorldPosition() == position) return false; // 이미 액터가 존재한다면 false   
    }
    
    return true; // 비어있다면 true
}

void GameLevel::OffScreenEnemySpawner()
{
    // 8방향 EnemySpawner TODO : 이거 이중 for문으로 할수있지않나? 
    Vector2 spawnerPosition[] = {
        Vector2(-80, -40), Vector2(0, -40), Vector2(80, -40),
        Vector2(-80, 0),                      Vector2(80, 0),
        Vector2(-80, 40), Vector2(0, 40), Vector2(80, 40)
    };   
    
    for (int i = 0; i < std::size(spawnerPosition); ++i)
    {        
        Vector2 position = playerActor->GetTransform()->GetWorldPosition() + spawnerPosition[i]; 
        std::shared_ptr<Actor> spawner = SpawnActor<EnemySpawner>(position);
        spawner->AttachTo(playerActor);
    }    
}
