#pragma once
#include <Actor/Actor.h>
#include "Util/Timer.h"

// 무기 레벨업 구상
// 나이프 : 그냥 많이, 자주쏨
// 성수 : 한번에 여러개날림
// 바이블 : 위성개수 늘어남
// 완드 : 여러 투사체가 여러 대상을 추적함([0]뿐아니라 [1] [2] 등등)
// 그 외 결합무기 : 화상, 빙결 등 능력을 가진 무기 추가 

enum class WeaponType
{
    Knife,
    Bible,
    HolyWater,
    MagicWand,
    Laser
};

struct WeaponData
{
    int weaponLevel;
    float damage;
    float fireInterval;
    float projectileSpeed;
    float knockBackForce;
};

class WeaponBase : public Craft::Actor
{
    TYPE_DECLARATIONS(WeaponBase, Actor)
    
/* Event */
public:
    WeaponBase(const Craft::Vector2& position);
    ~WeaponBase() = default;    
    
protected:
    virtual void Tick(float deltaTime) override;
    
/* Fire Projectile */
public:
    virtual void ShotProjectile(float directionX, float direction);
    
    WeaponData weaponData;
    
    WeaponType weaponType; // 업그레이드용
    
/* Flag */    
protected:    
    bool CanShot();  
    
    Timer cooldownTimer;   
    
/* Upgrade */
public:
    virtual void ApplyLevelAdjustment();
    
};
