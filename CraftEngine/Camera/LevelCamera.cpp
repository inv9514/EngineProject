#include "LevelCamera.h"
#include <Actor/Actor.h>
#include <Engine/Engine.h>

namespace Craft
{
    void LevelCamera::Tick(float deltaTime)
    {
        std::shared_ptr<Actor> targetActor = target.lock();
        if (!targetActor) return;            

        position = targetActor->GetWorldPosition();
    }
}