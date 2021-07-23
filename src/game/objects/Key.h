#ifndef KEY_H
#define KEY_H

#include "Actor.h"

namespace house {
    
    class Key : public Actor {
        private:
         static constexpr const char *Name        = "Key";
         static constexpr const char *TexturePath = "gfx\\objects\\key.png";

         static constexpr const char *PickedUpSoundPath
                                            = "sfx\\objects\\keyPickedUp.wav";
         Mix_Chunk_unique_ptr m_pickedUpSound;

         void onStart();
         void onSpawn();
         void onUpdate(float deltaTime);
        
        public:
         Key(Camera &camera, Vector2d<int> startingPosition);

         void onCollision(const Actor &other);
    };
    
} // namespace house

#endif // !KEY_H