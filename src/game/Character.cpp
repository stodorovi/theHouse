#include "Character.h"
#include "Level.h"

namespace house{

    Character::Character(Level * const level, const std::string &texturePath,
                         Camera &camera, const std::string &name,
                         const std::string &attackSoundPath,
                         const std::string &hitSoundPath,
                         const std::string &deathSoundPath,
                         Vector2d<int> startingPosition,
                         const std::string &tooltipInfo,
                         int health, int attackPower, bool collision)
    : Actor(texturePath, camera, name, startingPosition, collision,
            tooltipInfo),
    m_spriteSheetSize{0, 0}, m_action{Action::Idle},
    m_previousAction {Action::Idle}, m_movementDirection{Direction::Right},
    m_lastMovementDirection{Direction::None},
    m_facingDirection{Direction::Right},
    m_animationFrame{0.0f}, m_animationSpeed{16.0f},
    m_damageTakenDelay{static_cast<uint32_t>((SpriteSheetColumns /
                                              m_animationSpeed) * 1000)},
    m_alive {true}, m_InitialHealth{health}, m_maxHealth{health},
    m_health{health}, m_invincible{false}, m_attackPower {attackPower},
    m_attackSound{AudioManager::loadAudioWav(attackSoundPath)},
    m_hitSound{AudioManager::loadAudioWav(hitSoundPath)},
    m_deathSound{AudioManager::loadAudioWav(deathSoundPath)},
    m_level{level}
    {}

    void Character::onSpawn() {
        m_spriteSheetSize = m_size;

        m_screenSize.w /= SpriteSheetColumns;
        m_size.w /= SpriteSheetColumns;
        m_srcDrawRect.w = m_size.w;

        m_screenSize.h /= SpriteSheetRows;
        m_size.h /= SpriteSheetRows;
        m_srcDrawRect.h = m_size.h;
    }

    void Character::update(float deltaTime) {
        onUpdate(deltaTime);
        handleActions(deltaTime);

        m_previousAction = m_action;

        if (m_health <= 0) {
            onDeath(deltaTime);
        }
    }

    void Character::setMaxHealth(int newMaxHealth) noexcept {
        m_maxHealth = newMaxHealth;
    }

    void Character::setHealth(int newHealth) noexcept {
        if (newHealth > m_maxHealth) {
            m_health = m_maxHealth;
        }
        else if (newHealth < 1) {
            m_health = 0;
        }

        m_health = newHealth;
    }

    int Character::getHealth() const noexcept {
        return m_health;
    }

    void Character::setAttackPower(int newPower) noexcept {
        if (newPower < 0) {
            m_attackPower = 0;
        }

        m_attackPower = newPower;
    }

    int Character::getAttackPower() const noexcept {
        return m_attackPower;
    }

    void Character::animatedMove(float deltaTime) {
        if (static_cast< bool >(m_movementDirection) &&
            m_action != Action::Defending)
        {  
            bool continuingLeftward = static_cast<bool>(
                                            m_lastMovementDirection &
                                            Direction::Left) &&
                                      static_cast<bool>(
                                            m_movementDirection & 
                                            Direction::Left);

            bool continuingRightward = static_cast<bool>(
                                            m_lastMovementDirection &
                                            Direction::Right) &&
                                       static_cast<bool>(
                                            m_movementDirection &
                                            Direction::Right);

            bool movingLeftAndRight = static_cast<bool>(
                                            m_movementDirection &
                                            Direction::Left) &&
                                      static_cast<bool>(
                                            m_movementDirection &
                                            Direction::Right);

            bool continuingUpward = static_cast<bool>(
                                            m_lastMovementDirection &
                                            Direction::Up) &&
                                    static_cast<bool>(
                                            m_movementDirection &
                                            Direction::Up);

            bool continuingDownward = static_cast<bool>(
                                            m_lastMovementDirection &
                                            Direction::Down) &&
                                      static_cast<bool>(
                                            m_movementDirection &
                                            Direction::Down);

            bool movingUpAndDown = static_cast<bool>(
                                            m_movementDirection &
                                            Direction::Up) &&
                                   static_cast<bool>(
                                            m_movementDirection &
                                            Direction::Down);

            if (m_action == Action::Idle) {
                if (((continuingLeftward || continuingRightward) &&
                      !movingLeftAndRight) ||
                     (continuingUpward || continuingDownward) &&
                      !movingUpAndDown)
                {
                    m_animationFrame += deltaTime * m_animationSpeed;
                }
                else {
                    m_animationFrame = 0.0f;
                }

                m_srcDrawRect.y = m_size.h *
                                (static_cast<int>(continuingDownward) +
                                (static_cast<int>(continuingUpward) *
                                  UpwardWalkingSpriteSheetRow));
            }

            m_mirrored = static_cast<bool>(m_movementDirection &
                                           Direction::Left);

            if (static_cast<bool>(m_movementDirection &
                                  Direction::Up))
            {
                m_facingDirection = Direction::Up;
            }
            else if (static_cast<bool>(m_movementDirection &
                                       Direction::Down))
            {
                m_facingDirection = Direction::Down;
            }
            else if (static_cast<bool>(m_movementDirection &
                                       Direction::Left))
            {
                m_facingDirection = Direction::Left;
            }
            else if (static_cast<bool>(m_movementDirection &
                                       Direction::Right))
            {
                m_facingDirection = Direction::Right;
            }
            
            move(deltaTime, m_movementDirection);
        }
        else {
            if (m_action == Action::Idle) {
                m_animationFrame = 0.0f;
            }
        }

        m_srcDrawRect.x = static_cast<int>(m_animationFrame) * m_size.w;
        m_srcDrawRect.x %= (SpriteSheetFramesPerAnimation * m_size.w);
    }

    void Character::animatedFollow(float deltaTime, const Actor& followee) {
        auto followeePos = followee.getPosition();
        if (static_cast<int>(m_position.x) <
            static_cast<int>(followeePos.x))
        {
            m_movementDirection |= Direction::Right;
        }
        else if (static_cast<int>(m_position.x) >
                 static_cast<int>(followeePos.x))
        {
            m_movementDirection |= Direction::Left;
        }

        if (static_cast<int>(m_position.y) <
            static_cast<int>(followeePos.y))
        {
            m_movementDirection |= Direction::Down;
        }
        else if (static_cast<int>(m_position.y) >
                 static_cast<int>(followeePos.y))
        {
            m_movementDirection |= Direction::Up;
        }
    }

    void Character::handleActions(float deltaTime) {
        if (m_action == Action::Attacking) {
            attack(deltaTime);
        }
        else if (m_action == Action::Defending) {
            defend(deltaTime);
        }
        else if (m_action == Action::Idle &&
                 m_previousAction == Action::Defending) {
            stopDefending();
        }

        if ( m_action == Action::Idle) {
            m_lastMovementDirection = m_movementDirection;
            m_movementDirection = Direction::None;
        }
    }

    void Character::attack(float deltaTime) {
        if (m_action == Action::Attacking) {
            animateAttack(deltaTime);
        }
    }

    void Character::animateAttack(float deltaTime) {
        // first frame of attack
        if (m_previousAction != Action::Attacking) {
            if (m_facingDirection == Direction::Left ||
                m_facingDirection == Direction::Right)
            {
                m_srcDrawRect.y = SidewaysAttackSpriteSheetRow * m_size.y;

                // offset because of wider sprite
                if (m_facingDirection == Direction::Left) {
                    m_position.x -= (m_size.w / 2);
                }
            }
            // moving up or down
            else { 
                m_srcDrawRect.y = (DownwardAttackSpriteSheetRow +
                                   static_cast<int>(m_facingDirection ==
                                                    Direction::Up)) *
                                   m_size.h;
            }
            m_animationFrame = 0.0f;
        }
        if (m_facingDirection == Direction::Left ||
            m_facingDirection == Direction::Right)
        {
            if (m_size.w < m_spriteSheetSize.w / (SpriteSheetRows / 2)) {
                ++m_size.w;
                m_screenSize.w = static_cast<int>(m_size.w *
                                                  m_camera.getDrawScale());
                m_srcDrawRect.w = m_size.w;
            }
        }

        m_animationFrame += deltaTime * m_animationSpeed *
                          ((m_facingDirection == Direction::Down ||
                            m_facingDirection == Direction::Up) ?
                            2 : 1 );

        // end of attacking animation
        int spriteXPosPixel = static_cast< int >(m_animationFrame) * m_size.w;
        if (spriteXPosPixel >= m_spriteSheetSize.w) {
            m_animationFrame = 0.0f;
            m_action = Action::Idle;

            if (m_size.w != m_spriteSheetSize.w / SpriteSheetRows)
            {
                m_size.w = static_cast<int>(m_spriteSheetSize.w /
                                            SpriteSheetRows);
                m_screenSize.w = static_cast<int>(m_size.w *
                                                  m_camera.getDrawScale());
                m_srcDrawRect.w = m_size.w;
                
                // cancel the offset
                if ( m_facingDirection == Direction::Left )
                    m_position.x += m_size.w;
            }
            
            m_srcDrawRect.y = (SidewaysWalkingSpriteSheetRow +
                                (m_facingDirection == Direction::Down) +
                              (UpwardWalkingSpriteSheetRow *
                                (m_facingDirection == Direction::Up))) *
                               m_size.h;
        }
    }

    void Character::defend(float deltaTime) {
        
        m_srcDrawRect.y = DefendSpriteSheetRow * m_size.h;
        int defendFrame = 0;

        defendFrame = (DownwardsDefendColumn *
                       (m_facingDirection == Direction::Down)) +
                      (UpwardsDefendColumn *
                       (m_facingDirection == Direction::Up));
        m_srcDrawRect.x = defendFrame * m_size.w;
    }
    
    void Character::stopDefending() {
        m_srcDrawRect.y = (SidewaysDefendColumn +
                            (m_facingDirection == Direction::Down) +
                          (UpwardsDefendColumn *
                            (m_facingDirection == Direction::Up))) *
                           m_size.h;
        m_action = Action::Idle;
    }

    void Character::onDeath(float deltaTime) {
        deactivate();
        m_srcDrawRect.x = 0;
        m_srcDrawRect.y = DeadSpriteSheetRow *
                          (m_spriteSheetSize.h / SpriteSheetRows);

        m_size.w = m_spriteSheetSize.w / SpriteSheetColumns;
        m_size.h = m_spriteSheetSize.h / SpriteSheetRows;
        m_screenSize = m_size * m_camera.getDrawScale();
        m_deathSound.play();
    }

    Action Character::getCurrentAction() const noexcept {
        return m_action;
    }

    Direction Character::getFacingDirection() const noexcept {
        return m_facingDirection;
    }

    bool Character::characterInLineOfSight(const Character& other) {
        auto initialSize = m_size;

        auto initialPos = m_position;
        auto otherPos = other.getPosition() + (other.getSize() / 2);
        Direction directionToTarget = Direction::None;

        auto objects = m_level->getObjectsInsideCircle();

        int range = GameConstants::CircleSize.w;
        bool outOfRange = false;

        m_position = m_position + (m_size / 2);
        m_size = 1;

        while (!outOfRange) {
            directionToTarget = Direction::None;

            for (auto obj : objects) {
                if (obj != this && isCollidingWith(*obj)) {
                    m_position = initialPos;
                    m_size = initialSize;
                    return obj == &other;
                }
            }
            if (m_position.x != otherPos.x) {
                directionToTarget |= (m_position.x > otherPos.x) ?
                                     Direction::Left : Direction::Right;
            }
            if (m_position.y != otherPos.y) {
                directionToTarget |= (m_position.y > otherPos.y) ?
                                     Direction::Up : Direction::Down;
            }
            move(1.0f / m_movementSpeed, directionToTarget);
            

            outOfRange = (m_position - initialPos).abs().x > range ||
                         (m_position - initialPos).abs().y > range;
            

            if (outOfRange) {
                break;
            }
        }

        m_position = initialPos;
        m_size = initialSize;
        
        return false;
    }
} // namespace house