#include "Player.h"
#include <Component/BoxCollisionComponent.h>
#include <Engine/Engine.h>
#include <Level/Level.h>
#include <Input/Input.h>

#include <Component/RelativeSpriteRendererComponent.h>

#include "Projectile/ProjectileBase.h"
#include "Weapon/Knife.h"
#include "Weapon/WeaponBase.h"

using namespace Craft;

namespace
{
    int GetCollisionWidth(const Actor& actor)
    {
        std::shared_ptr<BoxCollisionComponent> collision = actor.GetComponent<BoxCollisionComponent>();
        return collision ? collision->GetWidth() : 0;
    }
}


Player::Player()
    : Actor(Vector2::Zero)
{
    // 컴포넌트 추가 
    AddComponent<RelativeSpriteRendererComponent>("V", Color::Yellow, 5);
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
    
    weaponList.emplace_back(knife);    
}

void Player::Tick(float deltaTime)
{
    super::Tick(deltaTime);
    
    ProcessInput(deltaTime);
}

void Player::OnCollision(const std::shared_ptr<Actor>& other)
{
    super::OnCollision(other);
}

void Player::Move(float moveDirectionX, float moveDirectionY, float deltaTime)
{
    positionX = positionX + moveDirectionX * moveSpeed * deltaTime;
    positionY = positionY + moveDirectionY * moveSpeed * deltaTime / 2;

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
        QuitGame();
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
        Fire();
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

void Player::Fire()
{
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return;
    
    /* 보유중인 모든 무기를 일제히 발사 (뱀서식) */
    for (const std::shared_ptr<WeaponBase>& weapon : weaponList)
    {
        if (!weapon || !weapon->IsActive()) continue;
              
        weapon->ShotProjectile(directionX, directionY);   // 방향값을 쥐어주고 무기에서 Projectile 생성요청
    }
}
