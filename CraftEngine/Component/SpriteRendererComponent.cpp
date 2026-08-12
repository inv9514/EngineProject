#include "SpriteRendererComponent.h"

#include <Actor/Actor.h>
#include <Render/Renderer.h>

namespace Craft
{
    SpriteRendererComponent::SpriteRendererComponent(const std::string& image, Color color, int sortingOrder)
    : image(image),color(color),sortingOrder(sortingOrder)
    {
    }

    void SpriteRendererComponent::Draw()
    {
        super::Draw();
        
        // Sprite 컴포넌트를 소유한 액터 확인
        std::shared_ptr<Actor> actor = GetOwner();
        
        if (!actor || !actor->IsActive()) return;
        
        // 액터가 갖고있는 Transform 컴포넌트를 가져옴
        std::shared_ptr<TransformComponent> transform = actor->GetTransform();
        if (!transform) return;
        
        // 렌더러에 드로잉 데이터를 제출
        Renderer::Get().Submit(image, transform->GetWorldPosition(), color, sortingOrder);
    
    }
}
