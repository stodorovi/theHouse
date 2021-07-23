#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <math.h>

#include "Vector2d.h"
#include "gameConstants.h"
#include "gameObjectTypes.h"

#include "GameException.h"

namespace house {

    enum class Direction {
        None  = 0,
        Up    = 1 << 0,
        Left  = 1 << 1,
        Down  = 1 << 2,
        Right = 1 << 3
    };

    inline Direction operator| (Direction lhs, Direction rhs) {
        return {static_cast<Direction>(static_cast<int>(lhs) |
                                       static_cast<int>(rhs))};
    }

    inline void operator|= (Direction &lhs, Direction rhs) {
        lhs = lhs | rhs;
    }

    inline Direction operator& (Direction lhs, Direction rhs) {
        return {static_cast<Direction>(static_cast<int>(lhs) &
                static_cast<int>(rhs))};
    }

    class GameObject{
        protected:
         std::string m_name;

         ObjectType m_type;

         bool m_isActive;

         Vector2d<float> m_position;

         float m_movementSpeed;

         bool m_mirrored;

        public:
         GameObject(const std::string &name = "GameObject",
                    Vector2d<int> startingPosition = {0, 0});
         virtual ~GameObject();
        
         /**
          * \brief Spawns the object, activating it & loading the texture
          * \returns Returns 1 on success, 0 on fail
          */
         virtual void spawn()   = 0;
         virtual void despawn() = 0;

         virtual void start();
         virtual void onStart() = 0;

         virtual void update(float deltaTime);
         virtual void onUpdate(float deltaTime) = 0;

         std::string getName() const noexcept;

         ObjectType getType() const noexcept;

         Vector2d<float> getPosition() const noexcept;
         void setPosition(Vector2d<float> newPosition) noexcept;
         void setPosition(float xPosition, float yPosition) noexcept;

         const bool isActive() const noexcept;
         void activate() noexcept;
         void deactivate() noexcept;
        
         void follow(float deltaTime, const GameObject& followee,
                     uint8_t distanceToKeep = 0) noexcept;

         void moveTo(float deltaTime, Vector2d<float> targetPosition,
                     uint8_t distanceToKeep = 0) noexcept;
        
         void move(float deltaTime, Direction direction) noexcept;

         template <typename T>
         static float distanceBetween(Vector2d<T> pos1,
                                      Vector2d<T> pos2) noexcept;

         float distanceFrom(Vector2d<float> position) const noexcept;
         float distanceFrom(const GameObject &object) const noexcept;
        
    };

} // namespace house

#endif // !GAME_OBJECT_H