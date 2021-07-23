#ifndef LEVEL_EXIT_H
#define LEVEL_EXIT_H

#include "Actor.h"

namespace house {

    class LevelExit : public Actor {
        private:
         static constexpr const char *Name = "Level Exit";
         static constexpr const char *TexturePath
                                           = "gfx\\objects\\levelExit.png";

         void onStart();
         void onSpawn();
         void onUpdate(float deltaTime);
        
        public:
         LevelExit(Camera &camera, Vector2d<int> startingPosition);

         void onCollision(const Actor &other);
    };
    
} // namespace house

#endif // !LEVEL_EXIT_H