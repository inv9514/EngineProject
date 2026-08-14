#include "Bible.h"

#include <cmath>
#include <Level/Level.h>

#include "Actor/Projectile/BibleProjectile.h"

using namespace Craft;

Bible::Bible(const Vector2& position)
    : super (position)
{
    isAlreadyExist = false;
}

void Bible::ShotProjectile(const float directionX, const float directionY)
{
    std::shared_ptr<Level> level = GetOwner();
    if (!level || isAlreadyExist) return;
    
    std::shared_ptr<BibleProjectile> projectile =
        level->SpawnActor<BibleProjectile>(Vector2::Zero,"##",Color::Blue,directionX,directionY);

    projectile->SetBibleIndex(0);
    projectile->AttachTo(shared_from_this(), false);
    
    std::shared_ptr<BibleProjectile> projectile2 =
        level->SpawnActor<BibleProjectile>(Vector2::Zero,"##",Color::Blue,directionX,directionY);

    projectile2->SetBibleIndex(1);
    projectile2->AttachTo(shared_from_this(), false);
    
    isAlreadyExist = true;
}
