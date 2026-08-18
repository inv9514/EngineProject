#include "ExplosiveActor.h"

#include "Component/RelativeSpriteRendererComponent.h"
#include <Component/BoxCollisionComponent.h>

#include "Actor/Enemy.h"
#include "Actor/Projectile/HolyWaterProjectile.h"

using namespace Craft;

ExplosiveActor::ExplosiveActor(const Craft::Vector2& position)
    : Actor (position)
{
    AddComponent<RelativeSpriteRendererComponent>("*", Color::BrightBlue, 1);
    AddComponent<BoxCollisionComponent>(1);    
    
    spriteRendererComponent = GetComponent<RelativeSpriteRendererComponent>();
                
    lifeSpanTimer.SetTargetTime(lifeSpan);
    colorTimer.SetTargetTime(0.08f);
}

void ExplosiveActor::Tick(float deltaTime)
{
    super::Tick(deltaTime);
    
    // 수명 종료시 액터 파괴 
    lifeSpanTimer.Tick(deltaTime);
    if (lifeSpanTimer.IsTimeOut()) Destroy(); 
    
    // 색상효과용
    colorTimer.Tick(deltaTime);
    if (colorTimer.IsTimeOut())
    {
        colorTimer.Reset();

        static const Color colors[] =
        {
            Color::Blue,
            Color::BrightBlue,
            Color::Cyan,
            Color::BrightCyan,
            Color::Cyan,
            Color::BrightBlue,
            Color::Blue
        };
        colorIndex = (colorIndex + 1) % 7;

        spriteRendererComponent->SetColor(colors[colorIndex]);
    }

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
        HolyWaterProjectile::totalDamage += damage;
    }
}
