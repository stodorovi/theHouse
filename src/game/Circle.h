#ifndef CIRCLE_H
#define CIRCLE_H

#include "Image.h"
#include "Actor.h"

namespace house {

    using namespace GameConstants;

    class CircleCollider : public Actor {
        private:
         friend class Circle;
         void setSize(Vector2d<int> newSize) noexcept;

         void onSpawn();
        
        public:
         CircleCollider(Camera &camera,
                        const std::string &name = "CircleCollider",
                        Vector2d<int> startingPosition = (CentrePosition -
                                                          CircleSize / 2),
                        Vector2d<int> size = CircleSize);

         void onStart();
         void onUpdate(float deltaTime);
         void onCollision(const Actor& other);
    };

    class Circle : public Actor {
        private:
         std::unique_ptr<CircleCollider> m_collider;

         static constexpr const char* BackgroundTexturePath
                                                = "gfx\\ui\\circle.png";
         static constexpr const char* ArrowTexturePath
                                                = "gfx\\ui\\circleArrow.png";

         std::unique_ptr<Image> m_background;
         std::unique_ptr<Image> m_arrow;

         void onSpawn();

        public:
         Circle(Camera &camera, double angle = 0.0);
        
         void spawn();
         void despawn();

         void onStart();
         void onUpdate(float deltaTime);

         void setAngle(float newAngle) noexcept;

         void setColliderSize(const Vector2d<int> newSize) noexcept;
         void onCollision(const Actor& other);

         void draw();

         const CircleCollider& getCollider() const noexcept;
    };

} // namespace house

#endif // !CIRCLE_H