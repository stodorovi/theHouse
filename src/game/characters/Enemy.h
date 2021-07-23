#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Player.h"

namespace house {

    class Enemy : public Character {
        private:
         /**
          * \brief This is an overriden empty function that should not be used.
          * Replaced by onUpdate(float, const Player&)
          */
         void onUpdate(float);

        protected:
         float m_attackChance;
         float m_defendChance;
         float m_followChance;

         void onUpdate(float deltaTime, const Player& player);
         virtual void think(float deltaTime, const Player& player) = 0;

         virtual void calculateAttackChance(const Player& player) = 0;
         virtual void calculateDefendChance(const Player& player) = 0;
         virtual void calculateFollowChance(const Player& player) = 0;

        public:
         Enemy(Level * const level, const std::string &texturePath,
               Camera &camera,
               const std::string &name = "NPC",
               const std::string &attackSoundPath = "",
               const std::string &hitSoundPath = "",
               const std::string &deathSoundPath = "",
               Vector2d<int> startingPosition = {0, 0},
               const std::string &tooltipInfo = "",
               int health = 1, int attackPower = 1,
               bool collision = true);

         void update(float deltaTime, const Player& player);

    };

} // namespace house

#endif // !ENEMY_H