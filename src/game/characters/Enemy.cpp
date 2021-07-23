#include "Enemy.h"

namespace house {
    
    Enemy::Enemy(Level * const level, const std::string &texturePath,
                 Camera &camera,
                 const std::string &name,
                 const std::string &attackSoundPath,
                 const std::string &hitSoundPath,
                 const std::string &deathSoundPath,
                 Vector2d<int> startingPosition,
                 const std::string &tooltipInfo,
                 int health, int attackPower,
                 bool collision)
    : Character(level, texturePath, camera, name,
                attackSoundPath, hitSoundPath, deathSoundPath,
                startingPosition, tooltipInfo,
                health, attackPower, collision),
      m_attackChance{0.0f}, m_defendChance{0.0f}, m_followChance{0.0f}
    {
        m_type = ObjectType::Enemy;
    }

    void Enemy::update(float deltaTime, const Player& player) {
        calculateAttackChance(player);
        calculateDefendChance(player);
        calculateFollowChance(player);

        onUpdate(deltaTime, player);
        handleActions(deltaTime);

        m_previousAction = m_action;

        if (m_health <= 0) {
            onDeath(deltaTime);
        }
    }
    
    void Enemy::onUpdate(float deltaTime, const Player& player) {
        think(deltaTime, player);
        animatedMove(deltaTime);
    }

    void Enemy::onUpdate(float) {}

} // namespace house