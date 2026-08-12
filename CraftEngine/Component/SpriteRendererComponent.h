#pragma once

#include <string>

#include "Component.h"
#include <Math/Color.h>

#include <Math/Vector2.h>

namespace Craft
{
    class CRAFT_API SpriteRendererComponent : public Component
    {
        TYPE_DECLARATIONS(SpriteRendererComponent, Component)
        
    public:
        SpriteRendererComponent(
            const std::string& image = "",
            Color color = Color::White,
            int sortingOrder = 0
            );
        
        virtual ~SpriteRendererComponent() = default;
    
        virtual void Draw() override;
        
        void Submit(const Vector2& position);
        
        inline const std::string& GetImage() const { return image;}
        inline void SetImage(const std::string& newImage) { image = newImage;}
        
        inline int GetWidth() const { return static_cast<int>(image.size()); }
        
        inline Color GetColor() const { return color; }
        inline void SetColor(Color newColor) { color = newColor; }
        
        inline int GetSortingOrder() const { return sortingOrder; }
        inline void SetSortingOrder(int newSortingOrder) { sortingOrder = newSortingOrder; }
        
        
    
    protected:
        std::string image;
        
        Color color = Color::White;
        
        int sortingOrder = 0;
    };
}

