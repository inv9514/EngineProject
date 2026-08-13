#include "RelativeSpriteRendererComponent.h"
#include <Component/TransformComponent.h>
#include <Actor/Actor.h>
#include <Engine/Engine.h>
#include <Math/Vector2.h>
#include <Level/Level.h>

using namespace Craft;

void RelativeSpriteRendererComponent::Draw()
{
    std::shared_ptr<Actor> actor = GetOwner();
    if (!actor || !actor->IsActive()) return;

    std::shared_ptr<TransformComponent> transform =
        actor->GetTransform();

    if (!transform) return;
    
    std::shared_ptr<Level> level = actor->GetOwner();
    if (!level) return;
    Vector2 cameraPosition = level->GetLevelCamera()->GetPosition();
    

    // 액터의 월드 위치
    Vector2 worldPosition = transform->GetWorldPosition();

    // 월드 좌표를 받으면 카메라 좌표와 조정을 거쳐 상대좌표로 변환
    Vector2 screenPosition = worldPosition - cameraPosition;

    // 카메라는 콘솔좌표 기준 중앙이므로 그만큼 위치값 가산
    screenPosition.x += Engine::Get().GetWidth() / 2 - 20;
    screenPosition.y += Engine::Get().GetHeight() / 2;

    // 변환된 위치를 Submit
    Submit(screenPosition);        
}
