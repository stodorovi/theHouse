#ifndef ACTOR_H
#define ACTOR_H

#include "DrawableObject.h"

namespace house {

    class Actor : public DrawableObject {
        protected:
         bool m_collidable;
        
        public:
         Actor(const std::string &texturePath, Camera &camera,
               const std::string &name = "Actor",
               Vector2d<int> startingPosition = {0, 0},
               bool collision = true, const std::string &tooltipInfo = "");

         Actor(Camera &camera, const std::string &name = "EmptyActor",
               Vector2d<int> startingPosition = {0, 0},
               Vector2d<int> size = {0, 0}, bool collision = true,
               const std::string &tooltipInfo = "");
         
         bool isCollidable() const noexcept;
         void activateCollision() noexcept;
         void deactivateCollision() noexcept;

         bool isCollidingWith(const Actor &other) const;
         void handleCollision(const Actor &other);

         virtual void onCollision(const Actor &other) = 0;

         void draw(Vector2d<int> offset = {0, 0});
         void draw(SDL_Texture &texture, Vector2d<int> offset = {0, 0});
    };

} // namespace house

#endif // !ACTOR_H