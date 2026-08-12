#include "Component.h"

namespace Craft
{
    Component::Component()
    {
    }

    Component::~Component()
    {
    }

    void Component::BeginPlay()
    {
        hasBeganPlay = true;
    }

    void Component::Tick(float DeltaTime)
    {
    }

    void Component::Draw()
    {
    }

    void Component::OnCollision(const std::shared_ptr<Actor>& other)
    {
    }
}
