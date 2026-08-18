#include "HolyWaterProjectile.h"
#include <Component/Component.h>
#include <Level/Level.h>
#include <Util/Util.h>

using namespace Craft;

float HolyWaterProjectile::totalDamage = 0.f;


HolyWaterProjectile::HolyWaterProjectile(
    const Vector2& position,
    const std::string& image,
    Color color,
    float directionX,
    float directionY,
    const WeaponData& weaponData)
    : super(
        position,
        image,
        color,
        directionX,
        directionY,
        weaponData)
{    
    lifeSpanTimer.SetTargetTime(Util::RandomRange(0.5f, 1.2f));
}

void HolyWaterProjectile::Tick(float deltaTime)
{
    // Actor::Tick 이벤트
    if (!IsActive()) return;			
    for (const std::shared_ptr<Component>& component : componentList) component->Tick(deltaTime);
    
    Move(directionX, directionY, deltaTime);   
    
    lifeSpanTimer.Tick(deltaTime);
    if (lifeSpanTimer.IsTimeOut())
    {
        // 폭발시작 
        std::shared_ptr<Level> level = GetOwner();
        if (level)
        {
            std::shared_ptr<ExplosiveSpawner> spawner =  level->SpawnActor<ExplosiveSpawner>(GetWorldPosition());
            spawner->CreateExplosiveActors();
        }
        
        Destroy();
    }
}

void HolyWaterProjectile::OnCollision(const std::shared_ptr<Actor>& other)
{
    // 성수는 Enemy와 상호작용 x 상위 Actor::OnCollision 직접호출 
    if (!IsActive()) return;
		
    for (const std::shared_ptr<Component>& component : componentList)
    {
        component->OnCollision(other);
    }	
}
