#pragma once
#include <Actor/Enemy.h>
#include <Util/Timer.h>

class EnemySpawner : public Craft::Actor
{
    TYPE_DECLARATIONS(EnemySpawner, Actor)
    
public:
    EnemySpawner(const Craft::Vector2& position);
    ~EnemySpawner() = default;
    
private:
    virtual void Tick(float deltaTime) override;
    
    void SpawnEnemy();  
    
private:
    Timer timer;
    
/* Spawn 파라미터 */
public:
    inline void SetSpawnInterval(const float& inSpawnInterval) { spawnInterval = inSpawnInterval; }
    inline float GetSpawnInterval() { return spawnInterval; }
    
private:
    float spawnInterval = 1.f;
};
