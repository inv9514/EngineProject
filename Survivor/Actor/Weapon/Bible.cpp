#include "Bible.h"

#include <cmath>
#include <Level/Level.h>

#include "Actor/Projectile/BibleProjectile.h"
#include <algorithm>
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


    cooldownTimer.SetTargetTime(weaponData.fireInterval);
}

void Bible::ShotProjectile(const float directionX, const float directionY)
{
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;

    if (spawnedBibleCount >= bibleProjectileCount)
        return;

    while (spawnedBibleCount < bibleProjectileCount)
    {
        std::shared_ptr<BibleProjectile> projectile =
            level->SpawnActor<BibleProjectile>(
                Vector2::Zero,
                "##",
                Color::Blue,
                directionX,
                directionY,
                weaponData);

        projectile->AttachTo(shared_from_this(), false);

        bibleProjectileList.push_back(projectile);

        ++spawnedBibleCount;
    }

    // 새 개수 기준으로 전체 바이블 각도 재배치
    const float angleInterval =
        2.f * 3.141592f / static_cast<float>(bibleProjectileCount);

    for (int i = 0; i < bibleProjectileList.size(); ++i)
    {
        if (!bibleProjectileList[i]) continue;

        bibleProjectileList[i]->SetAngle(
            angleInterval * static_cast<float>(i)
        );
    }
}

void Bible::ApplyLevelAdjustment()
{
    const int level = static_cast<int>(weaponData.weaponLevel);

    weaponData.damage = 7.f * (1.f + 0.05f * (level - 1));

    bibleProjectileCount = min(1 + (weaponData.weaponLevel - 1) / 2, 5);
}
