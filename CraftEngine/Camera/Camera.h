#pragma once
#include <Math/Vector2.h>

namespace Craft
{
    class CRAFT_API Camera
    {
    public:
        Camera(const Vector2& position = Vector2::Zero);

        void SetPosition(const Vector2& newPosition);

        inline Vector2 GetPosition() const { return position; }

        Vector2 ConvertWorldToScreen(const Vector2& worldPosition) const;

    private:
        Vector2 position = Vector2::Zero;
    
    };
}
