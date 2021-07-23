#include "DummySoldier.h"

namespace house {
    
    DummySoldier::DummySoldier(Level * const level, Camera &camera,
                               Vector2d<int> startingPosition)
    : Enemy(level, TexturePath, camera, Name,
            AttackSoundPath, HitSoundPath, DeathSoundPath,
            startingPosition, TooltipInfo)
    {
        m_type = ObjectType::Enemy;
    }

    void DummySoldier::onStart() {
        m_movementDirection = Direction::Left;
        m_invincible = true;
    }

    void DummySoldier::think(float deltaTime, const Player& player) {

    }

    void DummySoldier::tutorialAttack() {
        m_action = Action::Attacking;
        m_attackSound.play();
    }

    void DummySoldier::tutorialDefend() {
        m_action = Action::Defending;
        m_invincible = false;
    }

    void DummySoldier::onCollision(const Actor& other) {
        if (other.getType() == ObjectType::Player) {
            auto player = dynamic_cast<const Player*>(&other);
            auto playerPosition = player->getPosition();
            bool playerBehind = (playerPosition.x > m_position.x) &&
                                 m_facingDirection == Direction::Left ||
                                (playerPosition.x < m_position.x) &&
                                 m_facingDirection == Direction::Right ||
                                (playerPosition.y > m_position.y) &&
                                 m_facingDirection == Direction::Up ||
                                (playerPosition.y < m_position.y) &&
                                 m_facingDirection == Direction::Down;

            if (player->getCurrentAction() == Action::Attacking &&
               !m_invincible && (m_action != Action::Defending ||
                playerBehind) && m_damageTakenDelay.finished())
            {
                m_health -= player->getAttackPower();
                m_hitSound.play();
                m_damageTakenDelay.reset();
            }
        }
    }

    void DummySoldier::onDay(float deltaTime) {
        m_maxHealth = m_InitialHealth;

        if (m_health >= m_maxHealth) {
            m_health = m_maxHealth;
        }
    }

    void DummySoldier::onSunsetOrDawn(float deltaTime) {
        m_invincible = true;
    }

    void DummySoldier::onNight(float deltaTime) {
        m_invincible = false;
        m_maxHealth *= 2;
        m_health = m_maxHealth;
    }

    void DummySoldier::calculateAttackChance(const Player& player) {}
    void DummySoldier::calculateDefendChance(const Player& player) {}
    void DummySoldier::calculateFollowChance(const Player& player) {}

} // namespace house