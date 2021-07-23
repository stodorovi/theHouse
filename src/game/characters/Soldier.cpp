#include "Soldier.h"

namespace house {
    
    Soldier::Soldier(Level * const level, Camera &camera,
                     Vector2d<int> startingPosition)
    : Enemy(level, TexturePath, camera, Name,
            AttackSoundPath, HitSoundPath, DeathSoundPath,
            startingPosition, TooltipInfo)
    {
        m_movementSpeed *= 0.6f;
    }

    void Soldier::onStart() {

    }

    void Soldier::calculateAttackChance(const Player& player) {
        srand(static_cast<unsigned int>(time(0)));
        float chanceRoll = (rand() % 11) / 10.0f;
        
        m_attackChance = static_cast<float>((isCollidingWith(player) ||
                                            (player.getHealth() <= 3))) *
                         chanceRoll + static_cast<float>(m_invincible) / 2;
    }

    void Soldier::calculateDefendChance(const Player& player) {
        srand(static_cast<unsigned int>(time(0)));
        float chanceRoll = (rand() % 11) / 10.0f;

        m_defendChance = static_cast<float>((m_health <= m_maxHealth / 2) &&
                                            !m_invincible &&
                                             player.getHealth() >
                                              m_health * 2) *
                         chanceRoll;
    }

    void Soldier::calculateFollowChance(const Player& player) {
        srand(static_cast<unsigned int>(time(0)));
        float chanceRoll = (rand() % 11) / 10.0f;

        m_followChance = static_cast<float>(m_health > m_maxHealth / 2) *
                         chanceRoll + static_cast<int>(m_invincible) / 2;
    }

    void Soldier::think(float deltaTime, const Player& player) {
        if (player.isActive() &&
            characterInLineOfSight(dynamic_cast<const Character&>(player)))
        {
            if (m_followChance >= FollowThreshold &&
                !isCollidingWith(player))
            {
                animatedFollow(deltaTime, player);
                if (m_action != Action::Attacking) {
                    m_action = Action::Idle;
                }
            }

            if (m_defendChance >= DefendThreshold &&
                m_action != Action::Attacking)
            {
                m_action = Action::Defending;

                return;
            }

            if (m_attackChance >= AttackThreshold) {
                m_action = Action::Attacking;
                m_attackSound.play();

                return;
            }
        }
    }

    void Soldier::onCollision(const Actor& other) {
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

        if (other.getType() == ObjectType::Spikes) {
            auto projectile = dynamic_cast<const Spikes*>(&other);

            if (!m_invincible && m_action != Action::Defending &&
                 m_damageTakenDelay.finished())
            {
                --m_health;
                m_damageTakenDelay.reset();
                m_hitSound.play();
            }
        }
    }

    void Soldier::onDay(float deltaTime) {
        m_invincible = false;
        m_maxHealth = m_InitialHealth;

        if (m_health > m_maxHealth) {
            m_health = m_maxHealth;
        }
    }

    void Soldier::onSunsetOrDawn(float deltaTime) {
        m_invincible = true;
    }
    
    void Soldier::onNight(float deltaTime) {
        m_invincible = false;
        m_maxHealth = m_InitialHealth * 2;
        m_health = m_maxHealth;
    }

} // namespace house