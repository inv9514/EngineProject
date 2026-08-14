#include "ExplosiveActor.h"

#include "Component/RelativeSpriteRendererComponent.h"
#include <Component/BoxCollisionComponent.h>

#include "Actor/Enemy.h"

using namespace Craft;

ExplosiveActor::ExplosiveActor(const Craft::Vector2& position)
    : Actor (position)
{
    AddComponent<RelativeSpriteRendererComponent>("*", Color::BrightBlue, 7);
    AddComponent<BoxCollisionComponent>(1);    
    
    lifeSpanTimer.SetTargetTime(lifeSpan);
}

void ExplosiveActor::Tick(float deltaTime)
{
    super::Tick(deltaTime);
    
    lifeSpanTimer.Tick(deltaTime);
    if (lifeSpanTimer.IsTimeOut()) Destroy(); // 수명 종료시 액터 파괴
}

void ExplosiveActor::OnCollision(const std::shared_ptr<Actor>& other)
{
    super::OnCollision(other);
    
    if (other->IsTypeOf<Enemy>())
    {
        std::shared_ptr<Enemy> enemy = Cast<Enemy>(other);
        if (!enemy) return;
        
        HitStruct hitStruct(damage, Vector2::Zero);
       
        enemy->ReceiveHitStruct(hitStruct);
    }
}
