#include "DropActor.h"
#include <Math/Color.h>
#include <COmponent/BoxCollisionComponent.h>
#include "Actor/Player.h"
#include "Component/RelativeSpriteRendererComponent.h"

using namespace Craft;

DropActor::DropActor(const Craft::Vector2& position)
    : super (position)
{
    AddComponent<RelativeSpriteRendererComponent>("0", Color::Blue, 5);
    AddComponent<BoxCollisionComponent>(1);
    
    expAmount = 10;
}

void DropActor::OnCollision(const std::shared_ptr<Craft::Actor>& other)
{
    Actor::OnCollision(other);
    if (other->IsTypeOf<Player>())
    {
        std::shared_ptr<Player> player = Cast<Player>(other);
        if (!player) return;
        
        // 플레이어 경험치처리 로직
        player->ReceiveExp(expAmount);
        
        Destroy();
    }        
}
