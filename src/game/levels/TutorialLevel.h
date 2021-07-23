#ifndef TUTORIAL_LEVEL_H
#define TUTORIAL_LEVEL_H

#include <utility>

#include "Level.h"
#include "Game.h"

#include "Timer.h"

#include "TimeOfDayIcon.h"
#include "TimeOfDayEnum.h"

#include "PlayerLivesIcon.h"

#include "DummySoldier.h"

namespace house {

    class TutorialLevel : public Level {
        private:
         static constexpr const Vector2d<int> LevelSize{500, 128};

         std::array<TiledWall*, 7> m_firstBarrier;
         std::array<TiledWall*, 7> m_secondBarrier;
         std::array<TiledWall*, 7> m_thirdBarrier;

         float m_constTime;
        
         void createImages();
         void createButtons();
         void createWalls();
         void createEnemies();
         void createObjects();
         void createMissions();

         void createFirstBarier();
         void spawnFirstBarier();
         void despawnFirstBarier();

         void createSecondBarier();
         void spawnSecondBarier();
         void despawnSecondBarier();

         void createThirdBarier();
         void spawnThirdBarier();
         void despawnThirdBarier();

         void spawnFirstAndSecondBarrier();
         void despawnFirstAndSecondBarrier();

         void tooltipTutorial();
         void enemyApproachTutorial();
         void enemyDefenseTutorial();
         void enemyKillTutorial();

        public:
         TutorialLevel(Game &game, Camera &camera);

         void onStart();
         void onUpdate(float deltaTime);

         void onInput(float deltaTime);

         void onComplete();

         void onCollision(const Actor &other);

         void onUnload();
    };

} // namespace house

#endif // !TUTORIAL_LEVEL_H