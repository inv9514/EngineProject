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

    Vector2 center = GetWorldPosition();

    const int widths[] = { 6, 8, 10, 10, 8, 6 };

    for (int y = 0; y < 6; ++y)
    {
        int width = widths[y];

        int startX = -(width / 2);

        for (int x = 0; x < width; ++x)
        {
            Vector2 position(
                center.x + startX + x,
                center.y + y - 3
            );

            level->SpawnActor<ExplosiveActor>(position);
        }
    }
}
