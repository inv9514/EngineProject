#include "ExplosiveEffect.h"
#include <Engine/Engine.h>
#include <Component/SpriteRendererComponent.h>

using namespace Craft;
using EffectFrame = ExplosiveEffect::EffectFrame;

static const EffectFrame sequence[] = 
{
    { "  @  ", 0.08f, Color::BrightCyan },
    { " @@  ", 0.08f, Color::Cyan },
    { " @@@ ", 0.08f, Color::BrightBlue },
    { "@@@@ ", 0.08f, Color::Blue },
    { " @@@ ", 0.08f, Color::Cyan },
    { " @@  ", 0.08f, Color::BrightCyan },
    { "  @  ", 0.5f, Color::Gray },
};

ExplosiveEffect::ExplosiveEffect(const Vector2& position)
    : super(position)
{
    spriteRendererComponent 
    = AddComponent<RelativeSpriteRendererComponent>(sequence[0].frame, sequence[0].color, 7);
    
}

void ExplosiveEffect::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
}
