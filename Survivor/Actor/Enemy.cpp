#include "Enemy.h"

#include <iostream>
#include <valarray>
#include <Component/RelativeSpriteRendererComponent.h>
#include <Component/BoxCollisionComponent.h>
#include <Level/level.h>

#include "Component/StatusComponent.h"
#include "Projectile/ProjectileBase.h"

using namespace Craft;

int Enemy::enemyCount = 0;
int Enemy::killCount = 0;

Enemy::Enemy(const Vector2& position)
    : Actor(position)
{
    // 컴포넌트 추가 
    spriteRendererComponent = AddComponent<RelativeSpriteRendererComponent>("E", Color::Green, 5);
    AddComponent<BoxCollisionComponent>(1);
	
    // 생성 위치 설정 (Transform Component기반 콘솔 위치값)
    SetPosition(position);

    // 실제 위치 설정 (벡터 계산에 사용할 실제 액터의 위치값)
    positionX = static_cast<float>(position.x);
    positionY = static_cast<float>(position.y);
    
    // 이동 허가요청에 사용될 예측값
    desiredPositionX = positionX;
    desiredPositionY = positionY;
    
    // 피격 리액션 타이머
    reactionTimer.SetTargetTime(reactionDuration);
    
    // 레벨의 EnemyCount
    ++enemyCount;
}

void Enemy::BeginPlay()
{
    super::BeginPlay();
}

void Enemy::Tick(float deltaTime)
{    
    super::Tick(deltaTime);
    
    reactionTimer.Tick(deltaTime);
    
    // 피격관련 리액션 일괄처리
    if (reactionTimer.IsTimeOut())
    {
        spriteRendererComponent->SetColor(Color::Green);    
        moveSpeed = maxMoveSpeed;
    }    
}

void Enemy::OnCollision(const std::shared_ptr<Actor>& other)
{
    super::OnCollision(other);    
}

void Enemy::Destroy()
{
    super::Destroy();
    --enemyCount;
    ++killCount;
}


Vector2 Enemy::SubmitMoveRequest(const Vector2& targetPosition, float deltaTime)
{
    // 벡터 정규화하고 Direction 구하기
    Vector2 v1 = targetPosition - GetWorldPosition();
    float length = static_cast<float>(std::sqrt((v1.x)*(v1.x) + (v1.y)*(v1.y)));       
    if (length == 0.f) return GetWorldPosition();    
    float directionX = v1.x / length;
    float directionY = v1.y / length;

    // desiredPosition값이 누적되며 정수값 자리수가 바뀌는 순간 이동요청
    desiredPositionX += directionX * moveSpeed * deltaTime;
    desiredPositionY += directionY * moveSpeed * deltaTime;
    
    Vector2 requestPosition;    
    requestPosition.x = static_cast<int>(desiredPositionX);
    requestPosition.y = static_cast<int>(desiredPositionY);     

    return requestPosition;  
}

void Enemy::CommitMove(const Vector2& newPosition)
{
    // 이동요청 허가시 액터의 실제 위치값 갱신
    positionX = static_cast<float>(newPosition.x);
    positionY = static_cast<float>(newPosition.y);
    
    // 콘솔상 액터 위치 이동
    SetPosition(newPosition); 
}

void Enemy::MoveRejection()
{
    // 이동요청 거절시 축적된 desiredPosition값은 롤백되며 기존위치에서 다시 축적
    desiredPositionX = positionX;
    desiredPositionY = positionY;
}

void Enemy::TakeDamage(const float& damage)
{
    currentHp -= damage;    
    FlashHitEffect(Color::Red);
    
    if (currentHp <= 0.f) Destroy();
}

void Enemy::TakeKnockBack(const Vector2& forceVector)
{
    SetPosition(GetWorldPosition() - forceVector); 
    positionX = static_cast<int>(GetWorldPosition().x); 
    positionY = static_cast<int>(GetWorldPosition().y); 
    desiredPositionX = positionX; 
    desiredPositionY = positionY;
    
    moveSpeed = 0.f;
    reactionTimer.Reset();
}

void Enemy::FlashHitEffect(const Color& color)
{
    if (!spriteRendererComponent) return;
    
    spriteRendererComponent->SetColor(color);
    reactionTimer.Reset();
}
