#include "Player.h"
#include <Component/BoxCollisionComponent.h>
#include <Engine/Engine.h>
#include <Level/Level.h>
#include <Input/Input.h>

#include <Component/RelativeSpriteRendererComponent.h>

#include "Enemy.h"
#include "Game/Game.h"
#include "Projectile/ProjectileBase.h"
#include "Weapon/Bible.h"
#include "Weapon/HolyWater.h"
#include "Weapon/Knife.h"
#include "Weapon/Laser.h"
#include "Weapon/MagicWand.h"
#include "Weapon/WeaponBase.h"

using namespace Craft;

Player::Player()
    : Actor(Vector2::Zero)
{
    // 컴포넌트 추가 
    spriteRendererComponent = AddComponent<RelativeSpriteRendererComponent>("V", Color::Yellow, 7);
    AddComponent<BoxCollisionComponent>(1);
	
    // 생성 위치 설정
    int x = (Engine::Get().GetWidth() / 2);
    int y = (Engine::Get().GetHeight() / 2);
    SetPosition(Vector2(x, y));

    // 현재위치 저장 
    positionX = static_cast<float>(x);
    positionY = static_cast<float>(y);
}

void Player::BeginPlay()
{
    super::BeginPlay();
    
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    
    std::shared_ptr<Knife> knife = level->SpawnActor<Knife>(Vector2::Zero);
    knife->AttachTo(shared_from_this(), false);
    knife->weaponData.weaponLevel = 0; 
    
    std::shared_ptr<Bible> bible = level->SpawnActor<Bible>(Vector2::Zero);
    bible->AttachTo(shared_from_this(), false);
    bible->weaponData.weaponLevel = 0; 
    
    std::shared_ptr<MagicWand> wand = level->SpawnActor<MagicWand>(Vector2::Zero);
    wand->AttachTo(shared_from_this(), false);
    wand->weaponData.weaponLevel = 0;
    
    std::shared_ptr<HolyWater> holyWater = level->SpawnActor<HolyWater>(Vector2::Zero);
    holyWater->AttachTo(shared_from_this(), false);
    holyWater->weaponData.weaponLevel = 0;
    
    std::shared_ptr<Laser> laser = level->SpawnActor<Laser>(Vector2::Zero);
    laser->AttachTo(shared_from_this(), false);
    laser->weaponData.weaponLevel = 0;
    
    weaponList.push_back(knife);    
    weaponList.push_back(bible);
    weaponList.push_back(wand);
    weaponList.push_back(holyWater);    
    weaponList.push_back(laser);    
}

void Player::Tick(float deltaTime)
{
    super::Tick(deltaTime);
    
    ProcessInput(deltaTime);
    Fire();
}

void Player::OnCollision(const std::shared_ptr<Actor>& other)
{
    super::OnCollision(other);
    
    if (other->IsTypeOf<Enemy>())
    {
        std::shared_ptr<Enemy> enemy = Cast<Enemy>(other);
        if (!enemy) return;
        
        TakeDamage(1.f);
    }        
}

void Player::Move(float moveDirectionX, float moveDirectionY, float deltaTime)
{
    positionX = positionX + moveDirectionX * moveSpeed * deltaTime;
    positionY = positionY + moveDirectionY * moveSpeed * deltaTime; 

    Vector2 newPosition;
    newPosition.x = static_cast<int>(positionX);
    newPosition.y = static_cast<int>(positionY);
    SetPosition(newPosition);    
}

void Player::ProcessInput(float deltaTime)
{
    /* Engine Section */
    if (Input::Get().GetKeyDown(VK_ESCAPE))
    {        
        Game& game = dynamic_cast<Game&>(Engine::Get());
        game.OpenPauseMenu();
        return;
    }
    
    /* Movement Section */
    float moveDirectionX = 0.0f;
    float moveDirectionY = 0.0f;
    
    if (Input::Get().GetKey(VK_RIGHT))
    {
        moveDirectionX = 1.0f;
    }
    if (Input::Get().GetKey(VK_LEFT))
    {
        moveDirectionX = -1.0f;
    }
    if (Input::Get().GetKey(VK_UP))
    {
        moveDirectionY = -1.0f;
    }
    if (Input::Get().GetKey(VK_DOWN))
    {
        moveDirectionY = 1.0f;
    }

    Move(moveDirectionX, moveDirectionY, deltaTime);
    
    /* Weapon Section */
    if (Input::Get().GetKey(VK_SPACE))
    {
        // Fire();
    }
    
    /* Direction Section */
    if (Input::Get().GetKey(VK_RIGHT))
    {
        directionX = 1.f;
        directionY = 0.f;
    }
    if (Input::Get().GetKey(VK_LEFT))
    {
        directionX = -1.f;
        directionY = 0.f;
    }
    if (Input::Get().GetKey(VK_UP))
    {
        directionX = 0.f;
        directionY = -1.f;
    }
    if (Input::Get().GetKey(VK_DOWN))
    {
        directionX = 0.f;
        directionY = 1.f;
    }
    if (Input::Get().GetKey(VK_RIGHT) && Input::Get().GetKey(VK_UP))
    {
        directionX = 1.f;
        directionY = -1.f;
    }
    if (Input::Get().GetKey(VK_RIGHT) && Input::Get().GetKey(VK_DOWN))
    {
        directionX = 1.f;
        directionY = 1.f;
    }
    if (Input::Get().GetKey(VK_LEFT) && Input::Get().GetKey(VK_UP))
    {
        directionX = -1.f;
        directionY = -1.f;
    }
    if (Input::Get().GetKey(VK_LEFT) && Input::Get().GetKey(VK_DOWN))
    {
        directionX = -1.f;
        directionY = 1.f;
    }
}

void Player::TakeDamage(const float damage)
{
    playerLife -= damage;

    // 겜끝
    if (playerLife <= 0.f)
    {
        Game& game = dynamic_cast<Game&>(Engine::Get());
        game.OpenGameOverLevel();
    }
}

void Player::FlashHitEffect(const Craft::Color& color)
{
    if (!spriteRendererComponent) return;
    
    spriteRendererComponent->SetColor(color);
    reactionTimer.Reset();
}

void Player::Fire()
{
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    /* 보유중인 모든 무기를 일제히 발사 (뱀서식) */
    for (const std::shared_ptr<WeaponBase>& weapon : weaponList)
    {
        if (!weapon || !weapon->IsActive() || weapon->weaponData.weaponLevel == 0) continue;              
        weapon->ShotProjectile(directionX, directionY);   // 플레이어의 방향값만 넘겨주고 무기에서 Projectile 생성요청
    }
}

void Player::ReceiveExp(int expAmount)
{
    exp += expAmount;

    while (exp >= GetRequiredExp())
    {
        exp -= GetRequiredExp();
        ++playerLevel;
        
        Game& game = dynamic_cast<Game&>(Engine::Get());
        game.OpenSelectMenu();
        return;
    }
}

const int Player::GetRequiredExp()
{
    if (playerLevel <  20) return 5 + (playerLevel - 1) * 10;
    if (playerLevel == 20) return 795;
    if (playerLevel <  40) return 208 + (playerLevel - 21) * 13;
    return 458 + (playerLevel - 41) * 16;
}

void Player::UpgradeWeapon(WeaponType weaponType)
{
    for (const std::shared_ptr<WeaponBase>& weapon : weaponList)
    {
        if (!weapon) continue;

        if (weapon->weaponType == weaponType)
        {
            ++weapon->weaponData.weaponLevel;
            weapon->ApplyLevelAdjustment();
            return;
        }
    }
}

int Player::GetWeaponLevel(WeaponType type) const
{
    for (const std::shared_ptr<WeaponBase>& weapon : weaponList)
    {
        if (!weapon) continue;
        if (weapon->weaponType == type) return weapon->weaponData.weaponLevel;
    }
    return 0;
}
