#include "MagicWandProjectile.h"
#include <iostream>

#include "Actor/Enemy.h"

class Enemy;
using namespace Craft;

float MagicWandProjectile::totalDamage = 0.f;

void MagicWandProjectile::OnCollision(const std::shared_ptr<Actor>& other)
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
        Destroy();
    }        
}

