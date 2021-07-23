#ifndef WALL_H
#define WALL_H

#include "Actor.h"

namespace house {

    class TiledWall : public Actor {
        private:
         static constexpr const char *Name = "Wall";

         void onSpawn();

        public:
         TiledWall(Camera &camera, Vector2d<int> startingPosition = {0, 0},
                   Vector2d<int> size = {0, 0}, bool collidable = true);

         void onStart();
         void onUpdate(float deltaTime);
         void onCollision(const Actor &other);

         void follow(float deltaTime, const GameObject &followee,
                    uint8_t distanceToKeep = 0) noexcept = delete;

         void moveTo(float deltaTime, Vector2d<float> targetPosition,
                    uint8_t distanceToKeep = 0) noexcept = delete;

         void move(float deltaTime, Direction direction) noexcept = delete;
    };

} // namespace house

#endif // !WALL_H