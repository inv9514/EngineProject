#include "GameLevel.h"

#include <algorithm>
#include <Render/Renderer.h>
#include <Engine/Engine.h>
#include <Math/Vector2.h>
#include <Actor/EnemySpawner.h>
#include <Actor/Player.h>

#include "SelectLevel.h"
#include "Actor/Projectile/BibleProjectile.h"
#include "Actor/Projectile/HolyWaterProjectile.h"
#include "Actor/Projectile/KnifeProjectile.h"
#include "Actor/Projectile/LaserProjectile.h"
#include "Actor/Projectile/MagicWandProjectile.h"

using namespace Craft;


void GameLevel::OnInitialized()
{
    Level::OnInitialized();
    
    // 플레이어 생성
    playerActor = SpawnActor<Player>();
    
    // 쓰레기같은 방식이긴 한데 SelectLevel에 Player 전달성공
    std::shared_ptr<SelectLevel> select = selectLevel.lock();    
    if (select) select->SetPlayer(playerActor);
    
    // LevelCamera 등록(추적 대상 : Player)
    SetLevelCamera(std::make_shared<LevelCamera>(playerActor));
    
    // EnemySpawner 생성
    OffScreenEnemySpawner();            
}

void GameLevel::Tick(float deltaTime)
{
    Level::Tick(deltaTime);    
    
    WaveControl(deltaTime);
    
    uptime += deltaTime;
    waveLevel = static_cast<int>(uptime / 60.f) + 1;
}

void GameLevel::Draw()
{
    
    Level::Draw();

    // 구분선
    for (int y = 0; y < Engine::Get().GetHeight(); ++y)
    {
        SubmitUIRequestToRender(Vector2(110, y), "▒                                    ", Color::White);
    }

    // 업타임
    int totalSeconds = static_cast<int>(uptime);
    int minute = totalSeconds / 60;
    int second = totalSeconds % 60;

    std::string gameTimeText =
        std::to_string(minute) + ":" +
        (second < 10 ? "0" : "") +
        std::to_string(second);

    // 플레이어 좌표
    std::shared_ptr<LevelCamera> camera = GetLevelCamera();
    if (!camera) return;

    Vector2 cameraPosition = camera->GetPosition();

    std::string position =
        "< " + std::to_string(static_cast<int>(cameraPosition.x)) + ", "
        + std::to_string(static_cast<int>(cameraPosition.y)) + " >";

    // UI 정보
    SubmitUIRequestToRender(Vector2(117, 2),  gameTimeText, Color::White);
    SubmitUIRequestToRender(Vector2(117, 4),"Wave      : " + std::to_string(waveLevel),Color::White);
    SubmitUIRequestToRender(Vector2(117, 6),  "현재위치  : " + position, Color::White);
    SubmitUIRequestToRender(Vector2(117, 8),  "Enemy     : " + std::to_string(Enemy::GetEnemyCount()), Color::White);
    SubmitUIRequestToRender(Vector2(117, 10),  "KillCount : " + std::to_string(Enemy::GetKillCount()), Color::White);
    SubmitUIRequestToRender(Vector2(117, 12), "Level     : " + std::to_string(playerActor->GetCurrentLevel()), Color::White);
    SubmitUIRequestToRender(
        Vector2(117, 14),
        "EXP       : " + std::to_string(static_cast<int>(playerActor->GetCurrentExp()))
        + " / " + std::to_string(static_cast<int>(playerActor->GetCurrentRequiredExp())),
        Color::White
    );
    
    // 체력바
    std::string lifeText;
    int lifeCount = static_cast<int>(playerActor->GetPlayerLife() / 10.f);
    for (int i = 0; i < lifeCount; ++i) lifeText += "* ";
    SubmitUIRequestToRender(Vector2(117, 17), "Life      : " + lifeText, Color::BrightRed);  
    
    // Knife
    SubmitUIRequestToRender(Vector2(117, 20), "나이프", Color::White);
    SubmitUIRequestToRender(Vector2(117, 21), "현재 레벨  : " + std::to_string(playerActor->GetWeaponLevel(WeaponType::Knife)), Color::White);
    SubmitUIRequestToRender(Vector2(117, 22), "누적데미지 : " + std::to_string(static_cast<int>(KnifeProjectile::GetTotalDamage())), Color::White);

    // Bible
    SubmitUIRequestToRender(Vector2(117, 25), "성경", Color::White);
    SubmitUIRequestToRender(Vector2(117, 26), "현재 레벨  : " + std::to_string(playerActor->GetWeaponLevel(WeaponType::Bible)), Color::White);
    SubmitUIRequestToRender(Vector2(117, 27), "누적데미지 : " + std::to_string(static_cast<int>(BibleProjectile::GetTotalDamage())), Color::White);

    // HolyWater
    SubmitUIRequestToRender(Vector2(117, 30), "성수", Color::White);
    SubmitUIRequestToRender(Vector2(117, 31), "현재 레벨  : " + std::to_string(playerActor->GetWeaponLevel(WeaponType::HolyWater)), Color::White);
    SubmitUIRequestToRender(Vector2(117, 32), "누적데미지 : " + std::to_string(static_cast<int>(HolyWaterProjectile::GetTotalDamage())), Color::White);

    // MagicWand
    SubmitUIRequestToRender(Vector2(117, 35), "마법지팡이", Color::White);
    SubmitUIRequestToRender(Vector2(117, 36), "현재 레벨  : " + std::to_string(playerActor->GetWeaponLevel(WeaponType::MagicWand)), Color::White);
    SubmitUIRequestToRender(Vector2(117, 37), "누적데미지 : " + std::to_string(static_cast<int>(MagicWandProjectile::GetTotalDamage())), Color::White);

    // Laser
    SubmitUIRequestToRender(Vector2(117, 40), "레이저", Color::White);
    SubmitUIRequestToRender(Vector2(117, 41), "현재 레벨  : " + std::to_string(playerActor->GetWeaponLevel(WeaponType::Laser)), Color::White);
    SubmitUIRequestToRender(Vector2(117, 42), "누적데미지 : " + std::to_string(static_cast<int>(LaserProjectile::GetTotalDamage())), Color::White);

    
    DrawGroundDecorations();
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
            // playerActor->TakeDamage(5.f); -> Player로 이동
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
        if (!enemy || enemy == self) continue; // 본인 제외 

        if (enemy->GetWorldPosition() == position) return false;
    }
    
    return true;
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

void GameLevel::SubmitUIRequestToRender(const Vector2& position, const std::string& message, Color color)
{
    Renderer::Get().Submit(message, position, color, 10);
}

void GameLevel::DrawGroundDecorations() const
{
    const Vector2 cameraPosition = GetLevelCamera()->GetPosition();

    const int playAreaWidth = Engine::Get().GetWidth() - 40;
    const int playAreaHeight = Engine::Get().GetHeight();

    const int centerX = Engine::Get().GetWidth() / 2 - 20;
    const int centerY = Engine::Get().GetHeight() / 2;

    for (int screenY = 0; screenY < playAreaHeight; ++screenY)
    {
        for (int screenX = 0; screenX < playAreaWidth; ++screenX)
        {
            const int worldX = cameraPosition.x + screenX - centerX;
            const int worldY = cameraPosition.y + screenY - centerY;
            const uint32_t hash = MakePositionHash(worldX, worldY);

            if (hash % 600 != 0) continue;

            const std::string image = ((hash / 10) % 2 == 0) ? "`" : "\"";
            Renderer::Get().Submit(image,Vector2(screenX, screenY),Color::White,0);
        }
    }
}

uint32_t GameLevel::MakePositionHash(int x, int y)
{
    uint32_t hash = static_cast<uint32_t>(x) * 73856093u;
    hash ^= static_cast<uint32_t>(y) * 19349663u;

    hash ^= hash >> 13;
    hash *= 1274126177u;
    hash ^= hash >> 16;

    return hash;
}

void GameLevel::AddToDropActorList(std::shared_ptr<ExpActor> drops)
{
    dropActorList.emplace_back(drops);
}

void GameLevel::MoveAllDropActorsToPlayer()
{
    
}
