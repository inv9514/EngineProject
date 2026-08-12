#pragma once
#include "Core/CraftObject.h"

namespace Craft
{
    class Actor;
    
    class CRAFT_API Component : public CraftObject
    {
        TYPE_DECLARATIONS(Component, CraftObject)

    public:
        Component();
        virtual ~Component();
        
        virtual void BeginPlay();
        virtual void Tick(float DeltaTime);
        virtual void Draw();
        
        virtual void OnCollision(const std::shared_ptr<Actor>& other);
    
        inline bool HasBeganPlay() const { return hasBeganPlay; }
        inline std::shared_ptr<Actor> GetOwner() const { return owner.lock(); }
        inline void SetOwner(std::weak_ptr<Actor> newOwner) { owner = newOwner; }
    
    protected:
        bool hasBeganPlay = false;
        
        std::weak_ptr<Actor> owner;
    };

}
