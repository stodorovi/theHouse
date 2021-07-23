#ifndef DUMMY_SOLDIER_H
#define DUMMY_SOLDIER_H

#include <string.h>

#include "Enemy.h"
#include "Player.h"

namespace house {
    
    class DummySoldier : public Enemy {
        private:
         static constexpr const char *TexturePath
                                            = "gfx\\characters\\soldier.png";
        
         static constexpr const char *Name  = "Dummy Soldier";
         static constexpr const char *TooltipInfo
                                            = "This is a dummy.\n"
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

         void calculateAttackChance(const Player& player);
         void calculateDefendChance(const Player& player);
         void calculateFollowChance(const Player& player);

        public:
         DummySoldier(Level * const level, Camera &camera,
                      Vector2d<int> startingPosition = {0, 0});
        
         void onStart();
         void think(float deltaTime, const Player& player);

         void tutorialAttack();
         void tutorialDefend();

         void onDay(float deltaTime);
         void onSunsetOrDawn(float deltaTime);
         void onNight(float deltaTime);

         void onCollision(const Actor& other);
    };

} // namespace house

#endif // !DUMMY_SOLDIER_H