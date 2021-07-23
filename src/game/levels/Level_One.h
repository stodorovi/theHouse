#ifndef LEVEL_ONE_H
#define LEVEL_ONE_H

#include <utility>

#include "Level.h"
#include "Game.h"

#include "Timer.h"

#include "TimeOfDayIcon.h"
#include "TimeOfDayEnum.h"

#include "PlayerLivesIcon.h"

#include "Soldier.h"
#include "Wizard.h"

#include "Door.h"
#include "LockedDoor.h"
#include "Key.h"

#include "Spikes.h"

#include "LevelExit.h"

namespace house {
    
    class LevelOne : public Level {
        private:
         static constexpr const Vector2d<int> LevelSize{464, 464};
         static constexpr const char *Name = "House One";

         static constexpr const char *m_firstMissionTitle
                                                     = "First Blood";
         static constexpr const char *m_firstMissionDescription
                                                     = "Kill a Soldier\n"
                                                       " and a Wizard\n"
                                                       " to open the door.\n \n"
                                                       "REWARD: 1 HP";

         static constexpr const char *m_secondMissionTitle
                                                     = "Through\n"
                                                       " The Gates Of\n"
                                                       " The Silver Key";
         static constexpr const char *m_secondMissionDescription
                                                     = "Find a key to\n"
                                                       " open the exit\n"
                                                       " doors\n \n"
                                                       "REWARD: 2 HP";

         static constexpr const char *m_thirdMissionTitle
                                                     = "The End\n";
         static constexpr const char *m_thirdMissionDescription
                                                     = "Descend\n"
                                                       " the trapdoor \n"
                                                       " to exit the level.";

         Wizard *m_firstMissionWizard;
         Soldier *m_firstMissionSoldier;
         LockedDoor *m_firstMissionLockedDoor;

         Key *m_secondMissionKey;
         LockedDoor *m_secondMissionLockedDoor;

         LevelExit *m_levelExit;

         void createImages();
         void createButtons();
         void createWalls();
         void createEnemies();
         void createObjects();
         void createMissions();

         bool firstMissionCondition();
         void firstMissiononCompletion();

         bool secondMissionCondition();
         void secondMissiononCompletion();

         bool thirdMissionCondition();
         void thirdMissiononCompletion();

        public:
         LevelOne(Game &game, Camera &camera);

         void onStart();
         void onUpdate(float deltaTime);

         void onInput(float deltaTime);

         void onComplete();

         void onCollision(const Actor &other);

         void onUnload();
    };

} // namespace house

#endif // !LEVEL_ONE_H