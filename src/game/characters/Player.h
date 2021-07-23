#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

namespace house {

    class Player : public Character {
        private:
         static constexpr const char* Name = "Player";
         static constexpr const char* TooltipInfo
                                        = "This is you.\n Try not to die.";

         static constexpr const char* TexturePath
                                        = "gfx\\characters\\player.png";
        
         static constexpr const char* AttackSoundPath
                                        = "sfx\\characters\\playerAttack.wav";
         static constexpr const char* HitSoundPath
                                        = "sfx\\characters\\playerHit.wav";
         static constexpr const char* DeathSoundPath
                                        = "sfx\\characters\\playerDeath.wav";


         std::string m_killersName;

         void onInput(float deltaTime);

         friend class Game;
        public:
         Player(Level * const level, Camera &camera);

         void onStart();
         void onUpdate(float deltaTime);

         void onCollision(const Actor &other);

         void onDay(float deltaTime);
         void onSunsetOrDawn(float deltaTime);
         void onNight(float deltaTime);

         const std::string& getKillersName() const;
    };

} // namespace house

#endif // !PLAYER_H