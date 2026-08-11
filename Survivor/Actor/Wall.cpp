#include "Wall.h"
#include <Render/Renderer.h>
#include "Level/GameLevel.h"

using namespace Craft;

Wall::Wall(const Vector2& position)
    : Actor("#", position, Color::White)
{
    sortingOrder = 0;
}

void Wall::Draw()
{
    if (!IsActive()) return;

    // 자신을 소유한 Level 가져오기.
    std::shared_ptr<Level> owner = GetOwner();

    // 기본적으로는 자신의 월드 좌표를 사용.
    Vector2 screenPosition = position;

    if (owner && owner->IsTypeOf<GameLevel>())  // TODO : 이거 Tick단위 호출인데 캐스팅비용 크지않나?
    {
        // Level을 GameLevel로 형변환.
        std::shared_ptr<GameLevel> gameLevel = Craft::Cast<GameLevel>(owner);

        // Camera를 이용해 월드 좌표 → 화면 좌표 변환.
        screenPosition = gameLevel->GetCamera()->ConvertWorldToScreen(position);
    }

    // 변환된 화면 좌표로 렌더링 요청.
    Renderer::Get().Submit(image, screenPosition, color, sortingOrder); 
}
