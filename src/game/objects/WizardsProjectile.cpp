#include "WizardsProjectile.h"

namespace house {
    
    WizardsProjectile::WizardsProjectile(Camera &camera,
                                         Vector2d<int> startingPosition,
                                         int attackPower,
                                         Direction direction)
    : Actor(TexturePath, camera, Name, startingPosition),
    m_attackPower{attackPower}, m_moveDirection{direction}
    {
        m_type = ObjectType::Projectile;
    }

    void WizardsProjectile::onSpawn() {
        switch (m_moveDirection) {
            case Direction::Right:
                m_srcDrawRect = m_sidewaysSrcRect;
                break;

            case Direction::Left:
                m_srcDrawRect = m_sidewaysSrcRect;
                m_mirrored = true;
                break;

            case Direction::Up:
                m_srcDrawRect = m_upwardsSrcRect;
                break;

            case Direction::Down:
                m_srcDrawRect = m_downwardsSrcRect;
                break;
        }
    }

    void WizardsProjectile::onStart() {
        if (m_moveDirection == Direction::None) {
            m_moveDirection = Direction::Left;
        }
    }

    
    void WizardsProjectile::onUpdate(float deltaTime) {
        move(deltaTime, m_moveDirection);
    }

    void WizardsProjectile::onCollision(const Actor &other) {
        if (other.getType() != m_type) {
            despawn();
        }
    }

    int WizardsProjectile::getAttackPower() const noexcept {
        return m_attackPower;
    }
    
} // namespace house