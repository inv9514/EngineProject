#include <iostream>
#include <Level/Level.h>
#include <Engine/Engine.h>

#include "Level/GameLevel.h"

int main()
{
    Craft::Engine engine;
    engine.AddNewLevel<GameLevel>();
    engine.Run();
    
    
    // 레벨 생성
    
    
    std::cin.get();
}
