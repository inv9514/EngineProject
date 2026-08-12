#include "TransformComponent.h"

namespace Craft
{
    TransformComponent::TransformComponent(const Vector2& localPosition)
        : localPosition(localPosition), previousWorldPosition(localPosition)
    {
    }

    void TransformComponent::SavePreviousWorldPosition()
    {
        previousWorldPosition = GetWorldPosition();
    }

    Vector2 TransformComponent::GetWorldPosition() const
    {
        // 부모 트랜스폼
        std::shared_ptr<TransformComponent> parentTransform = parent.lock();
        
        // 부모가 없다면, 로컬 위치 = 월드 위치
        if (!parentTransform) return localPosition;
        
        // 부모가 있다면, 트랜스폼의 월드위치는 부모의 월드위치+트랜스폼 로컬위치 합산값
        return parentTransform->GetWorldPosition() + localPosition;
    }

    void TransformComponent::SetWorldPosition(const Vector2& newPosition)
    {
        // 부모 트랜스폼
        std::shared_ptr<TransformComponent> parentTransform = parent.lock();
        
        // 부모가 없다면, 로컬 위치 = 월드 위치
        if (!parentTransform) 
        {
            localPosition = newPosition;
            return;
        }
        
        // 월드 위치에서 부모 위치를 뺀값 = 로컬 위치
        localPosition = newPosition - parentTransform->GetWorldPosition();
    }
}
