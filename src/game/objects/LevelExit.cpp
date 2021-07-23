#include "LevelExit.h"

namespace house {
    
    LevelExit::LevelExit(Camera &camera, Vector2d<int> startingPosition)
    : Actor(TexturePath, camera, Name, startingPosition)
    {}

    void LevelExit::onSpawn() {
        
    }

    void LevelExit::onStart() {

    }

    
    void LevelExit::onUpdate(float deltaTime) {
        
    }

    void LevelExit::onCollision(const Actor &other) {
        
    }

} // namespace house