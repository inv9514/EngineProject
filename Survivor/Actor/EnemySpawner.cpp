#include "EnemySpawner.h"

#include <Level/Level.h>
#include <Util/Timer.h>
#include <Component/TransformComponent.h>
#include <Util/Util.h>

using namespace Craft;

EnemySpawner::EnemySpawner(const Vector2& position)
{
    GetTransform()->SetWorldPosition(position);
    
    timer.SetTargetTime(spawnInterval);
}

void EnemySpawner::Tick(float deltaTime)
{
    super::Tick(deltaTime);
    
    timer.Tick(deltaTime);
    if (!timer.IsTimeOut()) return;
    
    timer.Reset();
    
    SpawnEnemy();
}

void EnemySpawner::SpawnEnemy()
{
    Vector2 spawnPosition = GetTransform()->GetWorldPosition();
    
    const Vector2 randomPositonVariation(Vector2(Util::RandomRange(-5,5), Util::RandomRange(-5,5)));
    
    GetOwner()->SpawnActor<Enemy>(spawnPosition + randomPositonVariation);
}
