#ifndef WIZARD_H
#define WIZARD_H

#include <string.h>

#include "WizardsProjectile.h"
#include "Enemy.h"
#include "Player.h"

namespace house {
    
    class Wizard : public Enemy {
        private:
         static constexpr const char *TexturePath
                                            = "gfx\\characters\\wizard.png";
        
         static constexpr const char *Name  = "Wizard";
         static constexpr const char *TooltipInfo
                                            = "Mightiest sorcerer.\n"
                                              " in the land.\n"
                                              "He is invincible\n"
                                              "  during the night,\n"
                                              "Has thrice the\n"
                                              " power during dusk/dawn,\n"
                                              " and runs away from you\n"
                                              "  during the day.";
        
         static constexpr const char* AttackSoundPath
                                        = "sfx\\characters\\wizardAttack.wav";
         static constexpr const char* HitSoundPath
                                        = "sfx\\characters\\wizardHit.wav";
         static constexpr const char* DeathSoundPath
                                        = "sfx\\characters\\wizardDeath.wav";

         static constexpr float FollowThreshold = 0.5f;
         static constexpr float DefendThreshold = 0.4f;
         static constexpr float AttackThreshold = 0.2f;

         bool m_runAway;
         void runAway(const Player &player);

         void calculateAttackChance(const Player& player);
         void calculateDefendChance(const Player& player);
         void calculateFollowChance(const Player& player);

        public:
         Wizard(Level * const level, Camera &camera,
                Vector2d<int> startingPosition = {0, 0});
        
         void onStart();
         void think(float deltaTime, const Player& player);

         void onDay(float deltaTime);
         void onSunsetOrDawn(float deltaTime);
         void onNight(float deltaTime);

         void onCollision(const Actor& other);

         void shootProjectile(Direction direction);
    }; 

} // namespace house

#endif // !WIZARD_H