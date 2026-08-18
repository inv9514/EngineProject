#include "ExpActor.h"
#include <Math/Color.h>
#include <COmponent/BoxCollisionComponent.h>
#include "Actor/Player.h"
#include "Component/RelativeSpriteRendererComponent.h"

using namespace Craft;

ExpActor::ExpActor(const Craft::Vector2& position)
    : super(position)
{
    // TODO : 생성자에 경험치량 받고 Enemy에서 넘겨주기, 경험치량에 따라 렌더할 이미지 조건문
    AddComponent<RelativeSpriteRendererComponent>("o", Color::BrightBlue, 1);
    AddComponent<BoxCollisionComponent>(1);
    
    expAmount = 10;
}

void ExpActor::OnCollision(const std::shared_ptr<Craft::Actor>& other)
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
