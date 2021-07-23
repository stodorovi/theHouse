#ifndef LOCKED_DOOR_H
#define LOCKED_DOOR_H

#include "Actor.h"
#include "Door.h"

namespace house {

    class LockedDoor : public Actor {
        private:
         static constexpr const char *Name = "Locked Door";
         static constexpr const char *TexturePath
                                            = "gfx\\objects\\lockedDoor.png";

         const Orientation m_orientation;
         static constexpr SDL_Rect m_vertialSrcRect    {16, 0, 16, 32};
         static constexpr SDL_Rect m_horizontalSrcRect { 0, 0, 16, 16};

         void onStart();
         void onSpawn();
         void onUpdate(float deltaTime);
        
        public:
         LockedDoor(Camera &camera, Vector2d<int> startingPosition,
                    Orientation orientation);

         void onCollision(const Actor &other);
    };
    
} // namespace house

#endif // !DOOR_H