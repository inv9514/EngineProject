#pragma once

#include <Component/Component.h>

namespace Craft
{
    class CRAFT_API BoxCollisionComponent : public Component
    {
        TYPE_DECLARATIONS(BoxCollisionComponent, Component)
    public:
        BoxCollisionComponent(int width = 0);
        virtual ~BoxCollisionComponent() = default;
        
        inline int GetWidth() const { return width; }
        inline void SetWidth(int newWidth) { width = newWidth; }
    
    protected:
        int width = 0;
    };


}
