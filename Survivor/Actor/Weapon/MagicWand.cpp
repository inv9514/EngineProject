#include "MagicWand.h"

#include <cmath>
#include <Level/Level.h>
#include "Actor/Projectile/MagicWandProjectile.h"
#include "Level/GameLevel.h"

using namespace Craft;

MagicWand::MagicWand(const Craft::Vector2& position)
    : super(position)
{
    fireInterval = 10.f;
    fireTimer.Reset();
    fireTimer.SetTargetTime(fireInterval);
}

void MagicWand::ShotProjectile(const float directionX, const float directionY)
{
    if (!CanShot()) return;
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    std::shared_ptr<GameLevel> gameLevel = Cast<GameLevel>(level);
    if (!gameLevel) return;
    
    
    // 벡터 정규화하고 Direction 구하기
    Vector2 v1 = gameLevel->GetNearestEnemyPosition() - GetWorldPosition();
    float length = static_cast<float>(std::sqrt((v1.x)*(v1.x) + (v1.y)*(v1.y)));       
    if (length == 0.f) return;
    
    float homingDirectionX = v1.x / length;
    float homingDirectionY = v1.y / length;
    
    level->SpawnActor<MagicWandProjectile>(GetWorldPosition(), "*", Color::Cyan, homingDirectionX, homingDirectionY);
}
