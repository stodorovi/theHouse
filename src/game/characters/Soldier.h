#ifndef SOLDIER_H
#define SOLDIER_H

#include <string.h>

#include "Enemy.h"
#include "Player.h"

namespace house {

    class Soldier : public Enemy {
        private:
         static constexpr const char *TexturePath
                                           = "gfx\\characters\\soldier.png";
        
         static constexpr const char *Name = "Soldier";
         static constexpr const char *TooltipInfo
                                           = "This is a soldier.\n"
                                             " He is invincible\n"
                                             "  during the dusk/dawn,\n"
                                             " and he is twice as\n"
                                             " powerful during the night.\n";

         static constexpr const char* AttackSoundPath
                                        = "sfx\\characters\\soldierAttack.wav";
         static constexpr const char* HitSoundPath
                                        = "sfx\\characters\\soldierHit.wav";
         static constexpr const char* DeathSoundPath
                                        = "sfx\\characters\\soldierDeath.wav";

         static constexpr float FollowThreshold = 0.1f;
         static constexpr float DefendThreshold = 0.6f;
         static constexpr float AttackThreshold = 0.5f;

         void calculateAttackChance(const Player& player);
         void calculateDefendChance(const Player& player);
         void calculateFollowChance(const Player& player);

        public:
         Soldier(Level * const level, Camera &camera,
                 Vector2d<int> startingPosition = {0, 0});
        
         void onStart();
         void think(float deltaTime, const Player& player);

         void onDay(float deltaTime);
         void onSunsetOrDawn(float deltaTime);
         void onNight(float deltaTime);

         void onCollision(const Actor& other);
    };

} // namespace house

#endif // !SOLDIER_H