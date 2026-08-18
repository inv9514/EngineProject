#include "SelectLevel.h"

#include <algorithm>
#include <Util/Util.h>
#include "Game/Game.h"
#include <Engine/Engine.h>
#include <Input/Input.h>
#include <Render/Renderer.h>


using namespace Craft;

SelectLevel::SelectLevel()
{
    weaponList =
    {
        {
            WeaponType::Knife,
            "나이프",
            "/",
            Color::White,
            "전방의 적에게 피해를 입힙니다.",
            "탄속이 빠르고 적을 밀쳐냅니다."
        },

        {
            WeaponType::Bible,
            "성경",
            "##",
            Color::Blue,
            "플레이어 주위를 회전합니다.",
            "닿은 적에게 피해를 입힙니다."
        },

        {
            WeaponType::HolyWater,
            "성수",
            "&&",
            Color::Cyan,
            "구역에 피해를 주고 빙결시킵니다.",
            "폭발 영역은 잠시 유지됩니다."
        },

        {
            WeaponType::MagicWand,
            "마법지팡이",
            "*",
            Color::BrightPurple,
            "주위 적을 자동으로 추적합니다.",
            "적을 약간 밀쳐냅니다."
        },

        {
            WeaponType::Laser,
            "레이저",
            "-----",
            Color::BrightCyan,
            "탄속이 빠른 강력한 레이저.",
            "직선상의 적을 관통합니다."
        }
    };

    RefreshAugment();
    
}

void SelectLevel::Tick(float deltaTime)
{
    Level::Tick(deltaTime);

    if (RefreshAugmentFlag)
    {
        // 이게 맞나 싶지만 지금은 대안이 없다
        RefreshAugment();
        RefreshAugmentFlag = false;
    }

    const int length = static_cast<int>(selectionList.size());

    if (Input::Get().GetKeyDown(VK_LEFT))
    {
        currentIndex = (currentIndex - 1 + length) % length;
    }

    if (Input::Get().GetKeyDown(VK_RIGHT))
    {
        currentIndex = (currentIndex + 1) % length;
    }

    if (Input::Get().GetKeyDown(VK_RETURN))
    {
        itemList[currentIndex]->onSelected();
    }
}

void SelectLevel::Draw()
{
    Level::Draw();

    Renderer::Get().Submit("UPGRADE", Vector2(70, 3), Color::BrightRed);

    const int cardWidth = 40;
    const int cardHeight = 30;
    const int cardGap = 3;

    const int count = static_cast<int>(selectionList.size());
    const int totalWidth = cardWidth * count + cardGap * (count - 1);

    const int startX = (Engine::Get().GetWidth() - totalWidth) / 2;
    const int startY = 8;

    for (int ix = 0; ix < count; ++ix)
    {
        const int x = startX + ix * (cardWidth + cardGap);

        Color cardColor =
            (ix == currentIndex)
            ? selectedColor
            : unselectedColor;

        const WeaponSelectData& weapon = selectionList[ix];

        // 테두리
        for (int xOffset = 0; xOffset < cardWidth; ++xOffset)
        {
            Renderer::Get().Submit("#", Vector2(x + xOffset, startY), cardColor);
            Renderer::Get().Submit("#", Vector2(x + xOffset, startY + cardHeight - 1), cardColor);
        }

        for (int yOffset = 1; yOffset < cardHeight - 1; ++yOffset)
        {
            Renderer::Get().Submit("#", Vector2(x, startY + yOffset), cardColor);
            Renderer::Get().Submit("#", Vector2(x + cardWidth - 1, startY + yOffset), cardColor);
        }

        // 무기 데이터 출력
        Renderer::Get().Submit(weapon.name, Vector2(x + 4, startY + 2), cardColor);
        
        Renderer::Get().Submit(weapon.image, Vector2(x + 4, startY + 4), weapon.color);
        Renderer::Get().Submit("현재 레벨 : " + std::to_string(selectionList[ix].weaponLevel),
                  Vector2(x + 4, startY + 6),cardColor);
        
        Renderer::Get().Submit(weapon.descriptionA, Vector2(x + 4, startY + 10), cardColor);
        Renderer::Get().Submit(weapon.descriptionB, Vector2(x + 4, startY + 11), cardColor);
        
        
    }
}

void SelectLevel::RefreshAugment()
{
    itemList.clear();

    selectionList = weaponList;

    std::shuffle(
        selectionList.begin(),
        selectionList.end(),
        Util::GetRandomEngine());

    selectionList.resize(3);

    for (int ix = 0; ix < 3; ++ix)
    {
        const WeaponType weaponType = selectionList[ix].type;
        
        itemList.emplace_back(
            std::make_unique<MenuItem>(
                selectionList[ix].name,
                [this, weaponType]()
                {
                    std::shared_ptr<Player> targetPlayer = playerActor.lock();
                    if (!targetPlayer) return;

                    targetPlayer->UpgradeWeapon(weaponType);

                    RefreshAugmentFlag = true;

                    Game& game = dynamic_cast<Game&>(Engine::Get());
                    game.OpenGameLevel();
                }
            )
        );
    }
    
    currentIndex = 0;
    
    // 플레이어 레벨정보 Get
    auto targetPlayer = playerActor.lock();
    if (!targetPlayer) return;

    for (WeaponSelectData& weapon : selectionList)
        weapon.weaponLevel = targetPlayer->GetWeaponLevel(weapon.type);
}
