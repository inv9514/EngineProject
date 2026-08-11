#include "Camera.h"

#include "Engine/Engine.h"

namespace Craft
{
    
    Camera::Camera(const Vector2& position)
        : position(position)
    {
    }

    void Camera::SetPosition(const Vector2& newPosition)
    {
        position = newPosition;
    }

    Vector2 Camera::ConvertWorldToScreen(const Vector2& worldPosition) const
    {
        // 월드 좌표에서 카메라 위치를 빼서
        // 카메라를 기준으로 한 상대 위치를 계산
        Vector2 screenPosition = worldPosition - position;

        // 화면 중앙을 기준으로 표시
        screenPosition.x += Engine::Get().GetWidth() / 2;
        screenPosition.y += Engine::Get().GetHeight() / 2;

        return screenPosition;
    }

}
