#include "Bible.h"

#include <cmath>
#include <Level/Level.h>

#include "Actor/Projectile/BibleProjectile.h"

using namespace Craft;

Bible::Bible(const Vector2& position)
    : super (position)
{
    weaponData.weaponLevel = 1;
    weaponData.damage = 4.f;
    weaponData.projectileSpeed = 0.f;  // Bible은 발사체가 없고 공전궤도 사용
    weaponData.knockBackForce = 0.f;
    weaponData.fireInterval = 0.f;
    
    cooldownTimer.SetTargetTime(weaponData.fireInterval);
}

void Bible::ShotProjectile(const float directionX, const float directionY)
{
    if (isAlreadyExist) return;  // Bible은 투사체를 추가 생성하지 않음
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    std::shared_ptr<BibleProjectile> projectile =
        level->SpawnActor<BibleProjectile>
    (Vector2::Zero,"##",Color::Blue,directionX,directionY, weaponData);    
    
    std::shared_ptr<BibleProjectile> projectile2 =
        level->SpawnActor<BibleProjectile>
    (Vector2::Zero,"##",Color::Blue,directionX,directionY, weaponData);

    projectile->SetBibleIndex(0);
    projectile->AttachTo(shared_from_this(), false);
    
    projectile2->SetBibleIndex(1);
    projectile2->AttachTo(shared_from_this(), false);
    
    isAlreadyExist = true;
}
