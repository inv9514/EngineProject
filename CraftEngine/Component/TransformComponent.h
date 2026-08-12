#pragma once
#include "Component.h"
#include <Math/Vector2.h>


namespace Craft
{
    class CRAFT_API TransformComponent : public Component
    {
        TYPE_DECLARATIONS(TransformComponent, Component)
        
    public:
        TransformComponent(const Vector2& localPosition = Vector2::Zero);
        virtual ~TransformComponent() = default;                        
    
        inline Vector2 GetLocalPosition() const { return localPosition; }
        inline void SetLocalPosition(const Vector2& newPosition) { localPosition = newPosition; }

        Vector2 GetWorldPosition() const; 
        void SetWorldPosition(const Vector2& newPosition);
        
        // 충돌처리를 위한 이전 프레임 위치 저장/불러오기 
        inline Vector2 GetPreviousWorldPosition() const { return previousWorldPosition; }        
        void SavePreviousWorldPosition(); 
        
        // 컴포넌트 소유자 액터 접근
        inline std::shared_ptr<TransformComponent> GetParent() const { return parent.lock(); }
        inline void SetParent(std::weak_ptr<TransformComponent> newParent) { parent = newParent; }
        
    protected:
        // 부착대상(부모) 기준 위치
        Vector2 localPosition;
        
        // 이전 프레임 월드 위치
        Vector2 previousWorldPosition;
        
        // Scene Graph에서 부모가 되는 트랜스폼 컴포넌트 참조변수
        std::weak_ptr<TransformComponent> parent;
    };

}

