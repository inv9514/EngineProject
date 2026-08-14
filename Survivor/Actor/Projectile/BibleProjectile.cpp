#include "BibleProjectile.h"

#include <cmath>

#include "Actor/Enemy.h"

using namespace Craft;

BibleProjectile::BibleProjectile(
    const Craft::Vector2& position, 
    const std::string& image,
    Color color,
    const float directionX,
    const float directionY)
        :  super(position, "##", Color::Blue, directionX, directionY)
{
    damage = 20.f;
    knockBackForce = 4.f;
    moveSpeed = 0.f;
}

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
    }
        
}

void BibleProjectile::Tick(float deltaTime)
{
    if (!IsActive()) return;	
		
    for (const std::shared_ptr<Component>& component : componentList)
        component->Tick(deltaTime);
    
    Move(0, 0, deltaTime);  // 타겟디렉션 사용안함 = 0
}

void BibleProjectile::Move(float targetDirectionX, float targetDirectionY, float deltaTime)
{
    angle += angularSpeed * deltaTime;
    Vector2 localPosition;

    localPosition.x = static_cast<int>(std::cos(angle) * radius *2);
    localPosition.y = static_cast<int>(std::sin(angle) * radius);

    GetTransform()->SetLocalPosition(localPosition + Vector2(0, bibleIndex));
}
