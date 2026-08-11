#include "SurvivorActor.h"
#include <Render/Renderer.h>
#include <Engine/Engine.h>
#include <Level/Level.h>

#include "Level/GameLevel.h"

using namespace Craft;

void SurvivorActor::Draw()
{
    /* 기존 Draw : 액터의 position이 콘솔의 절대좌표 기준
        if (!IsActive()) return;		
        Renderer::Get().Submit(image, position, color, sortingOrder);  */
     
    /* 재정의한 Draw : Camera와 연계해서 Submit 하기전에 position의 벡터를 변환하고 Submit */    
    // 비활성 상태라면 그리지 않음.
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
