#include "LaserProjectile.h"
#include "Component/RelativeSpriteRendererComponent.h"
#include <Component/BoxCollisionComponent.h>
#include "Actor/Enemy.h"

using namespace Craft;

float LaserProjectile::totalDamage = 0.f;


LaserProjectile::LaserProjectile(
    const Vector2& position,
    const std::string& image,
    Color color,
    float directionX,
    float directionY,
    const WeaponData& weaponData)

    : ProjectileBase(
        position,
        image,
        color,
        directionX,
        directionY,
        weaponData)
{
    spriteRendererComponent = GetComponent<RelativeSpriteRendererComponent>();
    
    lifeSpan = 0.4f;
    lifeSpanTimer.SetTargetTime(lifeSpan);   
    colorTimer.SetTargetTime(0.08f);
}

void LaserProjectile::Tick(float deltaTime)
{
    if (!IsActive()) return;			
    for (const std::shared_ptr<Component>& component : componentList)
        component->Tick(deltaTime);
    
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
            Color::Cyan,
            Color::BrightWhite,
            Color::White,
            Color::Gray
        };
        colorIndex = (colorIndex + 1) % 5;

        spriteRendererComponent->SetColor(colors[colorIndex]);
    }
}

void LaserProjectile::OnCollision(const std::shared_ptr<Craft::Actor>& other)
{
    Actor::OnCollision(other);
    
    if (other->IsTypeOf<Enemy>())
    {
        std::shared_ptr<Enemy> enemy = Cast<Enemy>(other);
        if (!enemy) return;
        
        Vector2 knockBack = Vector2(
            static_cast<int>(directionX * knockBackForce * -1),
            static_cast<int>(directionY * knockBackForce * -1));
        
        HitStruct hitStruct(damage, knockBack);
       
        enemy->ReceiveHitStruct(hitStruct);    
        totalDamage += damage;
    }
}
