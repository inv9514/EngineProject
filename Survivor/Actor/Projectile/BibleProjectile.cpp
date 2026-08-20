#include "BibleProjectile.h"
#include <cmath>
#include "Actor/Enemy.h"

using namespace Craft;

float BibleProjectile::totalDamage = 0.f;


void BibleProjectile::OnCollision(const std::shared_ptr<Actor>& other)
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

void BibleProjectile::Tick(float deltaTime)
{
    /* Bible은 무브셋과 LifeSpan이 독특해 Tick 직접구현 */
    
    // Actor::Tick 파트
    if (!IsActive()) return;			
    for (const std::shared_ptr<Component>& component : componentList)
        component->Tick(deltaTime);
    
    Move(0, 0, deltaTime);
}

void BibleProjectile::Move(float targetDirectionX, float targetDirectionY, float deltaTime)
{
    angle += angularSpeed * deltaTime;

    Vector2 localPosition;

    localPosition.x =
        static_cast<int>(std::cos(angle) * radius * 2);

    localPosition.y =
        static_cast<int>(std::sin(angle) * radius);

    GetTransform()->SetLocalPosition(localPosition);
}