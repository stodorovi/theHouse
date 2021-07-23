#ifndef DOOR_H
#define DOOR_H

#include "Actor.h"
#include "Character.h"

namespace house {

    enum class Orientation {
        Vertical,
        Horizontal
    };

    class Door : public Actor {
        private:
         static constexpr const char *Name        = "Door";
         static constexpr const char *TexturePath = "gfx\\objects\\door.png";

         const Orientation m_orientation;
         static constexpr SDL_Rect m_vertialSrcRect    {16, 0, 16, 32};
         static constexpr SDL_Rect m_horizontalSrcRect { 0, 0, 16, 16};

         static constexpr const char *DestroyedSoundPath
                                        = "sfx\\objects\\doorDestroyed.wav";
         Mix_Chunk_unique_ptr m_destroyedSound;

         void onStart();
         void onSpawn();
         void onUpdate(float deltaTime);

         void breakDoor();
        
        public:
         Door(Camera &camera, Vector2d<int> startingPosition,
              Orientation orientation);

         void onCollision(const Actor &other);
    };

} // namespace house

#endif // !DOOR_H