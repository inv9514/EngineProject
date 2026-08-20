#include "Enemy.h"

#include <valarray>
#include <Component/RelativeSpriteRendererComponent.h>
#include <Component/BoxCollisionComponent.h>
#include <Level/level.h>

#include "Drops/DropActor.h"
#include "Drops/ExpActor.h"
#include "Level/GameLevel.h"
#include "Projectile/ProjectileBase.h"
#include <Util/Util.h>

#include "Drops/MagnetActor.h"

using namespace Craft;

int Enemy::enemyCount = 0;
int Enemy::killCount = 0;

Enemy::Enemy(const Vector2& position)
    : Actor(position)
{
    // 컴포넌트 추가 
    spriteRendererComponent = AddComponent<RelativeSpriteRendererComponent>("E", Color::Green, 6);
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
    reactionTimer.SetElapsedTime(reactionDuration);
    
    // 레벨의 EnemyCount
    ++enemyCount;        
}

void Enemy::BeginPlay()
{
    super::BeginPlay();
    
    // 레벨비례 스탯조정   
    std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
    if (!level) return; // 얘 왜 생성자에선 안되고 BeginPlay에선 true

    enemyLevel = level->GetWaveLevel();
    maxHp = maxHp + static_cast<float>(enemyLevel * 10); // 렙당 고정치 + 10
    currentHp = maxHp;
}

void Enemy::Tick(float deltaTime)
{    
    super::Tick(deltaTime);
    
    reactionTimer.Tick(deltaTime);
    
    if (isReacting)
    {
        // 피격 애니메이션 처리
        if (!reactionTimer.IsTimeOut())
        {
            float ratio = deltaTime / reactionDuration;

            positionX -= static_cast<int>(knockBackVector.x) * ratio;
            positionY -= static_cast<int>(knockBackVector.y) * ratio;

            Vector2 newPosition;
            newPosition.x = static_cast<int>(positionX);
            newPosition.y = static_cast<int>(positionY);

            SetPosition(newPosition);
        
            desiredPositionX = positionX;
            desiredPositionY = positionY;
        
            return;
        }
        
        // 애니메이션 타임 만료 후 원상복구
        spriteRendererComponent->SetColor(Color::Green);    
        moveSpeed = maxMoveSpeed;
        isReacting = false;
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
    
    // 얘네 하기전에 킵한번 해야겠다 이거
    std::shared_ptr<Level> level = GetOwner();
    if (!level) return; 
    std::shared_ptr<GameLevel> gameLevel = Cast<GameLevel>(level);
    if (!gameLevel) return;
    
  //  gameLevel->AddToDropActorList( level->SpawnActor<ExpActor>(GetWorldPosition()));  
    if (Util::RandomRange(1, 100) <= 50)
    {
        level->SpawnActor<ExpActor>(GetWorldPosition());  
    }
    
    // 5% 확률로 자석 드랍
    if (Util::RandomRange(1, 100) <= 50)
    {
        //level->SpawnActor<MagnetActor>(GetWorldPosition());
    }
    
    
}


Vector2 Enemy::SubmitMoveRequest(const Vector2& targetPosition, float deltaTime)
{
    // 벡터 정규화하고 Direction 구하기
    Vector2 v1 = targetPosition - GetWorldPosition();
    float length = static_cast<float>(std::sqrt((v1.x)*(v1.x) + (v1.y)*(v1.y)));       
    if (length == 0.f) return GetWorldPosition();    
    float directionX = v1.x / length;
    float directionY = v1.y / length;

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


void Enemy::ReceiveHitStruct(const HitStruct& hitStruct)
{
    isReacting = true;
    
    // 데미지 처리   
    currentHp -= hitStruct.damage;    
    
    // 피격이펙트 처리
    FlashHitEffect(Color::Red);
    
    // 사망처리
    if (currentHp <= 0.f)
    {
        // 나중에 Die함수로 빼고 이펙트처리 -> Destroy();
        Destroy();
    }
    
    knockBackVector = hitStruct.knockBackVector;
    moveSpeed = 0.f;
    
    reactionTimer.Reset();    
}

void Enemy::FlashHitEffect(const Color& color)
{
    if (!spriteRendererComponent) return;
    
    spriteRendererComponent->SetColor(color);
    reactionTimer.Reset();
}
