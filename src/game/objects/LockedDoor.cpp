#include "LockedDoor.h"

namespace house {
    
    LockedDoor::LockedDoor(Camera &camera, Vector2d<int> startingPosition,
                           Orientation orientation)
    : Actor(TexturePath, camera, Name, startingPosition),
    m_orientation{orientation}
    {}

    void LockedDoor::onSpawn() {
        if (m_orientation == Orientation::Horizontal) {
            m_srcDrawRect = m_horizontalSrcRect;
            m_size.h /= 2;
            m_screenSize.h /= 2;
        }
        else {
            m_srcDrawRect = m_vertialSrcRect;
        }

        m_size.w /= 2;
        m_screenSize.w /= 2;
    }

    void LockedDoor::onStart() {

    }

    
    void LockedDoor::onUpdate(float deltaTime) {
        
    }

    void LockedDoor::onCollision(const Actor &other) {

    }
    
} // namespace house