#include "GameObject.h"

namespace house {

    GameObject::GameObject(const std::string &name,
                           Vector2d<int> startingPosition)
    : m_name{name}, m_type{ObjectType::Object}, m_isActive{false},
    m_position{startingPosition},
    m_movementSpeed{100.0f}, m_mirrored{false}
    {}

    GameObject::~GameObject() {}

    void GameObject::start() {
        onStart();
    }
    
    void GameObject::update(float deltaTime) {
        onUpdate(deltaTime);
    }

    std::string GameObject::getName() const noexcept {
        return m_name;
    }

    ObjectType GameObject::getType() const noexcept {
        return m_type;
    }

    Vector2d<float> GameObject::getPosition() const noexcept {
        return m_position;
    };

    void GameObject::setPosition(Vector2d<float> newPosition) noexcept {
        m_position = newPosition;
    }

    void GameObject::setPosition(float xPosition, float yPosition) noexcept {
        m_position = {xPosition, yPosition};
    }

    const bool GameObject::isActive() const noexcept {
        return m_isActive;
    }

    void GameObject::activate() noexcept {
        m_isActive = true;
    };

    void GameObject::deactivate() noexcept {
        m_isActive = false;
    };

    void GameObject::follow(float deltaTime, const GameObject& followee,
                            uint8_t distanceToKeep) noexcept
    {
        moveTo(deltaTime, followee.getPosition(), distanceToKeep);
    }

    void GameObject::moveTo(float deltaTime,
                            Vector2d<float> targetPosition,
                            uint8_t distanceToKeep) noexcept
    {
        float distanceBetweenObjects = distanceFrom(targetPosition);
        if (distanceBetweenObjects > distanceToKeep) {
            Direction directionflags = Direction::None;

            Direction xDirection = (static_cast<int>(m_position.x) <
                                    static_cast<int>(targetPosition.x)) ?
                                    Direction::Right : Direction::Left;

            Direction yDirection = (static_cast<int>(m_position.y) <
                                    static_cast<int>(targetPosition.y)) ?
                                    Direction::Down : Direction::Up;
        
            if (static_cast<int>(m_position.x) !=
                static_cast<int>(targetPosition.x))
            {
                directionflags |= xDirection;
            }

            if (static_cast<int>(m_position.y) !=
                static_cast<int>(targetPosition.y))
            {
                directionflags |= yDirection;
            }

            move(deltaTime, directionflags);
        }
    }

    void GameObject::move(float deltaTime, Direction directionFlags) noexcept {
        int xDirection = (-1 * static_cast<int>(
                                static_cast<bool>(directionFlags &
                                                  Direction::Left))) +
                         (1 * static_cast<int>(
                               static_cast<bool>(directionFlags &
                                                 Direction::Right)));
        
        int yDirection = (-1 * static_cast<int>(
                                static_cast<bool>(directionFlags &
                                                  Direction::Up))) +
                         (1 * static_cast<int>(
                               static_cast<bool>(directionFlags &
                                                 Direction::Down)));

        bool diagonal = xDirection && yDirection;

        auto oldPosition = m_position;
        auto newPosition = m_position;

        if (diagonal) {
            double diagonalModifier = std::sqrt(std::pow(xDirection, 2) +
                                                std::pow(yDirection, 2));

            newPosition.x += static_cast<float>(
                                        xDirection *
                                        deltaTime *
                                        m_movementSpeed /
                                        static_cast<float>(diagonalModifier)
            );
            newPosition.y += static_cast<float>(
                                        yDirection *
                                        deltaTime *
                                        m_movementSpeed /
                                        static_cast<float>(diagonalModifier)
            );
        }
        else {
            newPosition.x += xDirection * deltaTime * m_movementSpeed;
            newPosition.y += yDirection * deltaTime * m_movementSpeed;
        }

        setPosition(newPosition);
    }

    template <typename T>
    float GameObject::distanceBetween(Vector2d<T> pos1,
                                      Vector2d<T> pos2) noexcept
    {
        Vector2d<float> distanceVector {pos1 - pos2};
        distanceVector.abs();
        
        float distance = static_cast<float>(std::sqrt(
                                             std::pow(distanceVector.x, 2) +
                                             std::pow(distanceVector.y, 2)));

        return distance;
    }

    float GameObject::distanceFrom(Vector2d<float> position) const noexcept{
        return distanceBetween<decltype(position.x)>(m_position, position);
    }

    float GameObject::distanceFrom(const GameObject &object) const noexcept {
        return distanceFrom(object.getPosition());
    }

} // namespace house
