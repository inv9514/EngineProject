#pragma once

#include <string>
#include <Actor/Actor.h>
#include "Component/RelativeSpriteRendererComponent.h"
#include <Util/Timer.h>

class ExplosiveEffect : public Craft::Actor
{
    TYPE_DECLARATIONS(ExplosiveEffect, Actor)
    
    struct EffectFrame
    {
        EffectFrame(const std::string& frame, float playTime, Craft::Color color)
            : frame(frame), playTime(playTime), color(color)
        {
        }
      
        ~EffectFrame() = default;
      
        std::string frame;      
        float playTime = 0.0f;      
        Craft::Color color = Craft::Color::White;
    };    

public:
    ExplosiveEffect(const Craft::Vector2& position);
    ~ExplosiveEffect() = default;

private:
    virtual void Tick(float deltaTime) override;

private:
    int effectSequenceCount = 0;

    int currentSequenceIndex = 0;

    Timer timer;

    std::shared_ptr<RelativeSpriteRendererComponent> spriteRendererComponent;
};
