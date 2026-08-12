#pragma once
#include <Component/SpriteRendererComponent.h>
#include <Math/Color.h>
#include <Math/Vector2.h>

/* 액터의 위치 = 콘솔 좌표계상의 위치인 기존 컴포넌트를 재정의해 
 * 액터의 위치를 카메라 위치값에 따라 조정해 상대적 위치에 드로우하는 컴포넌트  */
class RelativeSpriteRendererComponent : public Craft::SpriteRendererComponent
{
    TYPE_DECLARATIONS(RelativeSpriteRendererComponent, SpriteRendererComponent)
    
public:
    using SpriteRendererComponent::SpriteRendererComponent;
    
    virtual void Draw() override;
    
};
