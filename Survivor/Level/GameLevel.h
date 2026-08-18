#pragma once
#include <string>
#include <Level/Level.h>
#include <Actor/Player.h>
#include <Math/Vector2.h>
#include <Actor/Enemy.h>

// 액터 A와 액터 B가 존재함
// 레벨의 모든 액터는 순서대로 요청함. 
// 반복문에서 액터요청 - 레벨확인 - 비어있다면 해당위치에 점유됨 마크 - 액터에게 이동가능 true 리턴
// 다음 액터역시 똑같은 과정. 이를 모든 액터가 확인하고 한번에 이동함


class SelectLevel;

class GameLevel : public Craft::Level
{
    TYPE_DECLARATIONS(GameLevel, Level)
public:
    GameLevel() = default;
    ~GameLevel() = default;
    
/* 게임플레이 이벤트*/    
private:
    virtual void OnInitialized() override;
    virtual void Tick(float deltaTime) override;
    virtual void Draw() override;
    
/* Player 참조 */
private:
    std::shared_ptr<Player> playerActor;
    
/* Enemy Control Section */
private:
    void WaveControl(float deltaTime);             
    
    bool IsPositionEmpty(const Craft::Vector2& position, const std::shared_ptr<Enemy>& self);
    
    void OffScreenEnemySpawner();       

public:
    inline Craft::Vector2 GetNearestEnemyPosition() { return nearestEnemyPosition; }
    
private:
     Craft::Vector2 nearestEnemyPosition;
    
/* UI */
public:
    inline int GetWaveLevel() { return waveLevel; }

private:
    void SubmitUIRequestToRender(const Craft::Vector2& position, const std::string& message, Craft::Color color);
    
    float uptime = 0.f;
    
    int waveLevel = 1;
    
/* Player - SelectLevel 데이터 전송을 위한 참조 */    
public:
    inline void SetSelectLevel(const std::shared_ptr<SelectLevel>& newSelectLevel) { selectLevel = newSelectLevel; }

private:
    std::weak_ptr<SelectLevel> selectLevel;
  
/* Deco (이부분 코드 아직 이해못함) */
private:
    void DrawGroundDecorations() const;
    
    static uint32_t MakePositionHash(int x, int y);
    
};
