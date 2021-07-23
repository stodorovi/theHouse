#include "Circle.h"

namespace house {
    
    CircleCollider::CircleCollider(Camera &camera, const std::string &name,
                                   Vector2d<int> startingPosition,
                                   Vector2d<int> size)
    : Actor(camera, name, startingPosition, size, false)
    {}

    void CircleCollider::setSize(Vector2d<int> newSize) noexcept {
        m_size = newSize;
        m_screenSize = newSize;
    }

    void CircleCollider::onSpawn() {

    }

    void CircleCollider::onStart() {

    }

    void CircleCollider::onUpdate(float deltaTime) {

    }

    void CircleCollider::onCollision(const Actor& other) {

    }

    Circle::Circle(Camera &camera, double angle)
    : Actor(camera, "Circle", GameConstants::UICentrePosition),
    m_collider{std::make_unique<CircleCollider>(camera)},
    m_background{nullptr}, m_arrow{nullptr}
    {
        m_background = std::move(
                        std::make_unique<Image>(BackgroundTexturePath,
                                                m_camera));

        m_arrow = std::move(std::make_unique<Image>(ArrowTexturePath,
                                                    m_camera));
    }

    void Circle::spawn() {
        m_background->spawn();
        m_arrow->spawn();
        m_spawned = m_arrow->isSpawned() && m_background->isSpawned();

        onSpawn();
    }

    void Circle::onSpawn() {
        activate();
    }

    void Circle::despawn() {
        m_background->despawn();
        m_arrow->despawn();
        m_spawned = false;
    }

    void Circle::onStart() {
        m_background->start();
        m_arrow->start();
    }

    void Circle::onUpdate(float deltaTime) {
        m_collider->setPosition(m_camera.getPosition() -
                                (GameConstants::CircleSize / 2));
        m_arrow->setAngle(m_arrow->getAngle() + deltaTime);
    }

    void Circle::setAngle(float newAngle) noexcept {
        m_arrow->setAngle(newAngle);
    }

    void Circle::setColliderSize(Vector2d<int> newSize) noexcept {
        m_collider->setSize(newSize);
    }

    void Circle::onCollision(const Actor& other) {

    }

    const CircleCollider& Circle::getCollider() const noexcept {
        return *m_collider;
    }

    void Circle::draw() {
        if (m_background->isSpawned()) {
            m_background->draw();
        }

        if (m_arrow->isSpawned()) {
            m_arrow->draw();
        }
    }
    
} // namespace house