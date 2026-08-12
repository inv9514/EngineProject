#pragma once
#include <memory>
#include <Math/Vector2.h>
#include <Core/CraftObject.h>
#include <Actor/Actor.h>

namespace Craft
{
    class CRAFT_API LevelCamera : public CraftObject
    {
        TYPE_DECLARATIONS(LevelCamera, CraftObject)
        
    public:
        LevelCamera(const std::shared_ptr<Actor>& target)
            : target(target)
        {
            
        }
        
        void Tick(float deltaTime);
        
        inline const Vector2& GetPosition() const { return position;}
        
        inline void SetPosition(const Vector2& newPosition) { position = newPosition; }
        
    

    private:
        Vector2 position = Vector2::Zero;
        
        std::weak_ptr<Actor> target;
    
    };
}
