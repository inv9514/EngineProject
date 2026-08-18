#pragma once

#include <Level/Level.h>
#include <vector>
#include "MainMenuLevel.h"
#include "Actor/Player.h"
#include "Actor/Weapon/WeaponBase.h"


struct WeaponSelectData
{
    WeaponType type;

    std::string name;
    std::string image;
    Craft::Color color;
    std::string descriptionA;
    std::string descriptionB;

    int weaponLevel;
};

class SelectLevel : public Craft::Level
{
    TYPE_DECLARATIONS(SelectLevel, Level)
    
/* Event */    
public:
    SelectLevel();

    void Tick(float deltaTime) override;
    void Draw() override;

/* Selection */
private:
    std::vector<std::unique_ptr<MenuItem>> itemList;

    int currentIndex = 0;

    Craft::Color selectedColor = Craft::Color::Yellow;
    Craft::Color unselectedColor = Craft::Color::White;
    
/* Item */    
public:
    void RefreshAugment();  // 증강목록 렙업마다 리셋
    
private:
    std::vector<WeaponSelectData> weaponList;
    
    std::vector<WeaponSelectData> selectionList;
    
private:
    bool RefreshAugmentFlag = true;     
    
/* Upgrade 상호작용을 위한 Player 참조 */   
public:
    inline void SetPlayer(const std::shared_ptr<Player>& newPlayer) { playerActor = newPlayer; }
    
private:
    std::weak_ptr<Player> playerActor;    
};
