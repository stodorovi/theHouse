#include "Wall.h"

namespace house {  
    
    TiledWall::TiledWall(Camera &camera, Vector2d<int> startingPosition,
                         Vector2d<int> size, bool collidable)
    : Actor(camera, Name, startingPosition, size)
    {}

    void TiledWall::onStart() {
        
    }

    void TiledWall::onSpawn() {
        
    }

    void TiledWall::onUpdate(float deltaTime) {

    }

    void TiledWall::onCollision(const Actor &other) {
        
    }

} // namespace house