
#pragma once

#include <Camera/Camera.h>
#include <Level/Level.h>


class GameLevel : public Craft::Level
{
    TYPE_DECLARATIONS(GameLevel, Level)
    
public:
    GameLevel();
        
private:
    virtual void OnInitialized() override;
    
    void LoadMap(const std::string& filename);   
    
    /* Camera Section */
public:
    inline Craft::Camera* GetCamera() const { return camera.get(); }
    
private:
    std::unique_ptr<Craft::Camera> camera;
};
