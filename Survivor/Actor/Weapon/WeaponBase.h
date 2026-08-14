#pragma once
#include <Actor/Actor.h>
#include "Util/Timer.h"

// 무기 레벨업 구상
// 나이프 : 그냥 많이, 자주쏨
// 성수 : 한번에 여러개날림
// 바이블 : 위성개수 늘어남
// 완드 : 여러 투사체가 여러 대상을 추적함([0]뿐아니라 [1] [2] 등등)

struct WeaponDataStruct
{
    float damage;
    float fireInterval;
    float projectileSpeed;
};

class WeaponBase : public Craft::Actor
{
    TYPE_DECLARATIONS(WeaponBase, Actor)
    
public:
    WeaponBase(const Craft::Vector2& position);
    ~WeaponBase() = default;    
    
    virtual void ShotProjectile(const float directionX, const float directionY);
    
protected:
    virtual void Tick(float deltaTime) override;
    
    bool CanShot();  
    
    float fireInterval = 0.2f; 
    
    Timer fireTimer;
};
