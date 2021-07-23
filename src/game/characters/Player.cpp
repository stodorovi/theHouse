#include "Player.h"
#include "Enemy.h"
#include "WizardsProjectile.h"

namespace house {
    
    Player::Player(Level * const level, Camera &camera)
    :Character(level, TexturePath, camera, Name, AttackSoundPath, HitSoundPath,
               DeathSoundPath, GameConstants::CentrePosition, TooltipInfo)
    {
        m_type = ObjectType::Player;
    }

    void Player::onStart() {
        
    }

    void Player::onUpdate(float deltaTime) {
        onInput(deltaTime);
        animatedMove(deltaTime);
    }

    void Player::onInput(float deltaTime) {

        auto keys = SDL_GetKeyboardState(NULL);
        if (m_action == Action::Idle) {
            if (keys[SDL_SCANCODE_A]) {
                m_movementDirection |= Direction::Left;
            }
            if (keys[SDL_SCANCODE_D]) {
                m_movementDirection |= Direction::Right;
            }
            if (keys[SDL_SCANCODE_W]) {
                m_movementDirection |= Direction::Up;
            }
            if (keys[SDL_SCANCODE_S]) {
                m_movementDirection |= Direction::Down;
            }
        }

        if (keys[SDL_SCANCODE_LCTRL] && m_action != Action::Attacking) {
            m_action = Action::Attacking;
            m_attackSound.play();
        }

        if (keys[SDL_SCANCODE_LALT] && m_action != Action::Attacking) {
            m_action = Action::Defending;
        }
        else if (!keys[SDL_SCANCODE_LALT] && m_action == Action::Defending) {
            m_action = Action::Idle;
        }
    }

    void Player::onCollision(const Actor &other) {
        int beginHealth = m_health;

        if (other.getType() == ObjectType::Enemy) {
            auto enemy = dynamic_cast<const Enemy*>(&other);

            if (enemy->getCurrentAction() == Action::Attacking &&
               !m_invincible && m_action != Action::Defending &&
                m_damageTakenDelay.finished())
            {
                m_health -= enemy->getAttackPower();
                m_damageTakenDelay.reset();
            }
        }

        if (other.getType() == ObjectType::Projectile) {
            auto projectile = dynamic_cast<const WizardsProjectile*>(&other);

            if (!m_invincible && m_action != Action::Defending &&
                 m_damageTakenDelay.finished())
            {
                m_health -= projectile->getAttackPower();
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

        int endHealth = m_health;

        if (endHealth != beginHealth && endHealth <= 0 && beginHealth > 0) {
            m_killersName = other.getName();
        }
    }
    
    void Player::onDay(float deltaTime) {

    }

    void Player::onSunsetOrDawn(float deltaTime) {

    }

    void Player::onNight(float deltaTime) {

    }

    const std::string& Player::getKillersName() const {
        return m_killersName;
    }

} // namespace house