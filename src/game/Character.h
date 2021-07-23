#ifndef CHARACTER_H
#define CHARACTER_H

#include "Actor.h"
#include "Timer.h"
#include "Spikes.h"

namespace house {

    enum class Action {
        Idle,
        Attacking,
        Defending,
    };

    class Level;
    class Character : public Actor {
        protected:
         static constexpr int SpriteSheetFramesPerAnimation = 8;
         static constexpr int SpriteSheetRows               = 8;
         static constexpr int SpriteSheetColumns            = 8;

         static constexpr int SidewaysWalkingSpriteSheetRow = 0;
         static constexpr int DownwardWalkingSpriteSheetRow = 1;
         static constexpr int UpwardWalkingSpriteSheetRow   = 2;
         static constexpr int SidewaysAttackSpriteSheetRow  = 3;
         static constexpr int DownwardAttackSpriteSheetRow  = 4;
         static constexpr int UpAttackSpriteSheetRow        = 5;
         static constexpr int DefendSpriteSheetRow          = 6;
         static constexpr int DeadSpriteSheetRow            = 7;

         static constexpr int SidewaysDefendColumn          = 0;
         static constexpr int DownwardsDefendColumn         = 1;
         static constexpr int UpwardsDefendColumn           = 2;

         Vector2d <int> m_spriteSheetSize;

         Action m_action;
         Action m_previousAction;

         Direction m_movementDirection;
         Direction m_lastMovementDirection;

         Direction m_facingDirection;

         float m_animationFrame;
         float m_animationSpeed;

         Timer m_damageTakenDelay;

         bool m_alive;
         const int m_InitialHealth;
         int m_maxHealth;
         int m_health;
         bool m_invincible;

         int m_attackPower;

         Mix_Chunk_unique_ptr m_attackSound;
         Mix_Chunk_unique_ptr m_hitSound;
         Mix_Chunk_unique_ptr m_deathSound;

         Level * m_level;

         void onSpawn();

         void handleActions(float deltaTime);

         void animateAttack(float deltaTime);
        
         void stopDefending();

         void onDeath(float deltaTime);

        public:
         static const uint8_t DefaultNumberOfLives = 6;

         Character(Level * const level, const std::string &texturePath,
                   Camera &camera, const std::string &name = "Character",
                   const std::string &attackSoundPath = "",
                   const std::string &hitSoundPath = "",
                   const std::string &deathSoundPath = "",
                   Vector2d<int> startingPosition = {0, 0},
                   const std::string &tooltipInfo = "",
                   int health = DefaultNumberOfLives, int attackPower = 1,
                   bool collision = true);

         void update(float deltaTime);

         void setMaxHealth(int newMaxHealth) noexcept;
         void setHealth(int newHealth) noexcept;
         int getHealth() const noexcept;

         void setAttackPower(int newPower) noexcept;
         int getAttackPower() const noexcept;

         void animatedMove(float deltaTime);

         void animatedFollow(float deltaTime, const Actor& followee);

         void attack(float deltaTime);

         void defend(float deltaTime);

         Action getCurrentAction() const noexcept;
         Direction getFacingDirection() const noexcept;

         bool characterInLineOfSight(const Character& other);

         virtual void onDay(float deltaTime) = 0;
         virtual void onSunsetOrDawn(float deltaTime) = 0;
         virtual void onNight(float deltaTime) = 0;
    };

} // namespace house

#endif // !CHARACTER_H