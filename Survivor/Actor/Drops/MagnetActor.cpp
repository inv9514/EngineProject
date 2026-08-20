#include "MagnetActor.h"
#include <Math/Color.h>
#include <COmponent/BoxCollisionComponent.h>
#include "Actor/Player.h"
#include "Component/RelativeSpriteRendererComponent.h"
#include "Level/GameLevel.h"

using namespace Craft;


MagnetActor::MagnetActor(const Craft::Vector2& position)
{
    AddComponent<RelativeSpriteRendererComponent>("0", Color::BrightRed, 6);
    AddComponent<BoxCollisionComponent>(1);
}

void MagnetActor::OnCollision(const std::shared_ptr<Craft::Actor>& other)
{
    Actor::OnCollision(other);
    if (other->IsTypeOf<Player>())
    {
        std::shared_ptr<Player> player = Cast<Player>(other);
        if (!player) return;
        
        std::shared_ptr<Level> level = GetOwner();
        if (!level) return;
        
        std::shared_ptr<GameLevel> gameLevel = Cast<GameLevel>(level);
        if (!gameLevel) return;
        
        gameLevel->MoveAllDropActorsToPlayer();
        
        Destroy();
    }        
}
