#pragma once

#include <Actor/Actor.h>

#include "Util/Timer.h"


class RelativeSpriteRendererComponent;
class StatusComponent;

class Enemy : public Craft::Actor
{
    TYPE_DECLARATIONS(Enemy, Actor)    

public:
    Enemy(const Craft::Vector2& position);    
    
/* Event */    
private:
    virtual void BeginPlay() override;	
    virtual void Tick(float deltaTime) override;
    virtual void OnCollision(const std::shared_ptr<Actor>& other) override;
    virtual void Destroy() override;
    
    
/* Enemy Count */
public:
    inline static int GetEnemyCount() {  return enemyCount; }
    
    inline static int GetKillCount() {  return killCount; }
    
private:
    static int enemyCount;      
    
    static int killCount;
    
/* Movement */    
public:
    // 레벨에 액터 이동요청 
    Craft::Vector2 SubmitMoveRequest(const Craft::Vector2& targetPosition, float deltaTime); 
    
    // 이동 요청이 허가되었을 경우 액터 이동
    void CommitMove(const Craft::Vector2& newPosition);
    
    // 이동 요청이 거절되었을 경우 desiredPosition값 롤백
    void MoveRejection();
    
private:    
    // 콘솔 좌표계상의 Transform-position이 아닌 액터의 실제 누적되는 좌표값
    float positionX = 0.0f;  
    float positionY = 0.0f;  
    
    // 이동요청시 사용될 롤백 여부를 고려한 좌표값
    float desiredPositionX = 0.f;
    float desiredPositionY = 0.f;
    
/* Stats */
    float maxHp = 10.f;
    
    float currentHp = 10.f;
    
    float maxMoveSpeed = 5.f;
    
    float moveSpeed = 5.f;
    
    
/* Combat */
public:
    void TakeDamage(const float& damage);
    
    void TakeKnockBack(const Craft::Vector2& forceVector);
    
private:
    void FlashHitEffect(const Craft::Color& color);
    
private:    
    Timer reactionTimer;
    
    float reactionDuration = 0.4f; 
    
    Craft::Vector2 knockBackDirection;
    
    float knockBackSpeed = 15.f;
    
    std::shared_ptr<RelativeSpriteRendererComponent> spriteRendererComponent;
};

