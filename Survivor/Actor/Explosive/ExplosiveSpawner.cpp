#include "ExplosiveSpawner.h"

#include "ExplosiveActor.h"
#include <Level/Level.h>
using namespace Craft;


ExplosiveSpawner::ExplosiveSpawner(const Craft::Vector2& position)
    : Actor(position)
{
}

void ExplosiveSpawner::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
}

void ExplosiveSpawner::CreateExplosiveActors()
{
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    level->SpawnActor<ExplosiveActor>(GetWorldPosition());
}
