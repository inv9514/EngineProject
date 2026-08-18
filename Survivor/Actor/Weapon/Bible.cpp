#include "Bible.h"

#include <cmath>
#include <Level/Level.h>

#include "Actor/Projectile/BibleProjectile.h"

using namespace Craft;

Bible::Bible(const Vector2& position, int weaponLevel)
    : super (position)
{
    weaponType = WeaponType::Bible;

    // 현재 무기 레벨
    weaponData.weaponLevel = weaponLevel;

    // 레벨과 상관없는 고정값
    weaponData.projectileSpeed = 0.f;
    weaponData.knockBackForce = 0.f;
    weaponData.fireInterval = 0.f;

    // 현재 레벨에 따른 값 계산
    ApplyLevelAdjustment();

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

void Bible::ApplyLevelAdjustment()
{
    weaponData.damage = 7.f * (1.f + 0.05f * static_cast<int>(weaponData.weaponLevel - 1));
}
