#include "Wizard.h"
#include "Level.h"

namespace house {
    
    Wizard::Wizard(Level * const level, Camera &camera,
                   Vector2d<int> startingPosition)
    :Enemy(level, TexturePath, camera, Name,
            AttackSoundPath, HitSoundPath, DeathSoundPath,
            startingPosition, TooltipInfo, 2, 2),
    m_runAway{false}
    {}

    void Wizard::onStart() {
        m_movementSpeed *= 0.5f;
    }

    void Wizard::runAway(const Player &player) {
        auto playerPos = player.getPosition();

        Direction runDirection;
        if (m_position.x < playerPos.x) {
            runDirection |= Direction::Left;
        }
        else {
            runDirection |= Direction::Right;
        }

        if (m_position.y < playerPos.y) {
            runDirection |= Direction::Up;
        }
        else {
            runDirection |= Direction::Down;
        }

        m_movementDirection = runDirection;
    }

    void Wizard::calculateAttackChance(const Player& player) {
        srand(static_cast<unsigned int>(time(0)));
        float chanceRoll = (rand() % 11) / 10.0f;
        
        m_attackChance = static_cast<float>(((m_health == m_maxHealth ||
                                              player.getHealth() <= 3))) *
                         chanceRoll;
    }
    void Wizard::calculateDefendChance(const Player& player) {
        srand(static_cast<unsigned int>(time(0)));
        float chanceRoll = (rand() % 11) / 10.0f;

        m_defendChance = (static_cast<float>((m_health <= m_maxHealth / 2) &&
                                             !m_invincible) +
                          static_cast<float>(player.getHealth() >
                                             m_health * 4) / 2) *
                          chanceRoll;
    }
    void Wizard::calculateFollowChance(const Player& player) {
        srand(static_cast<unsigned int>(time(0)));
        float chanceRoll = (rand() % 11) / 10.0f;

        m_followChance = static_cast<float>((m_health > m_maxHealth / 2) ||
                                             m_invincible) *
                         chanceRoll;
    }

    void Wizard::think(float deltaTime, const Player& player) {
        if (player.isActive() &&
            characterInLineOfSight(dynamic_cast<const Character&>(player)))
        {
            if (m_runAway) {
                runAway(player);
            }
            else {
                if (m_followChance >= FollowThreshold &&
                   !isCollidingWith(player))
                {
                    animatedFollow(deltaTime, player);
                    if (m_action != Action::Attacking) {
                        m_action = Action::Idle;
                    }
                }

                if (m_defendChance >= DefendThreshold &&
                    m_action == Action::Idle)
                {
                    m_action = Action::Defending;

                    return;
                }

                if (m_attackChance >= AttackThreshold &&
                    m_action != Action::Attacking)
                {
                    m_action = Action::Attacking;
                    if (m_previousAction != Action::Attacking) {
                        shootProjectile(Direction::Up);
                        shootProjectile(Direction::Down);
                        shootProjectile(Direction::Left);
                        shootProjectile(Direction::Right);
                        m_attackSound.play();
                    }

                    return;
                }
            }
        }
    }

    void Wizard::onCollision(const Actor& other) {
        if (other.getType() == ObjectType::Player) {
            auto player = dynamic_cast<const Player*>(&other);
            auto playerPosition = player->getPosition();
            bool playerBehind = ((playerPosition.x > m_position.x) &&
                                  m_facingDirection == Direction::Left) ||
                                ((playerPosition.x < m_position.x) &&
                                  m_facingDirection == Direction::Right) ||
                                ((playerPosition.y > m_position.y) &&
                                  m_facingDirection == Direction::Up) ||
                                ((playerPosition.y < m_position.y) &&
                                 m_facingDirection == Direction::Down);

            if (player->getCurrentAction() == Action::Attacking &&
              !m_invincible && (m_action != Action::Defending ||
              playerBehind) && m_damageTakenDelay.finished())
            {
                m_health -= player->getAttackPower();
                m_damageTakenDelay.reset();
                m_hitSound.play();
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

    void Wizard::onDay(float deltaTime) {
        m_maxHealth = m_InitialHealth;
        m_health = m_maxHealth;

        if (m_attackPower / 3) {
            m_attackPower /= 3;
        }

        m_runAway = true;
    }
    void Wizard::onSunsetOrDawn(float deltaTime) {
        if (m_invincible) {
            m_invincible = false;
        }

        if (m_runAway) {
            m_runAway = false;
        }

        m_maxHealth = m_InitialHealth * 3;
        m_health = m_maxHealth;
        m_attackPower *= 3;
    }
    void Wizard::onNight(float deltaTime) {
        if (m_attackPower / 3) {
            m_attackPower /= 3;
        }

        m_invincible = true;
    }

    void Wizard::shootProjectile(Direction direction) {
        m_level->m_objects.emplace_back(std::move(
                                         std::make_unique<WizardsProjectile>(
                                            m_camera,
                                            Vector2d<int>{
                                                static_cast<int>(m_position.x),
                                                static_cast<int>(m_position.y)
                                            },
                                            m_attackPower,
                                            direction)
                                        )
        );

        m_level->m_objects.back()->spawn();
        m_level->m_objects.back()->start();
    }

} // namespace house