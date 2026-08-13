#include "StatusComponent.h"
#include <Actor/Actor.h>

void StatusComponent::Tick(float DeltaTime)
{
    Component::Tick(DeltaTime);
    
    if (health <= 0) owner.lock()->Destroy();
}

void StatusComponent::TakeDamage(float inDamage)
{
    health -= inDamage;
}

