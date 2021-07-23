#ifndef LEVEL_H
#define LEVEL_H

#include "Actor.h"
#include "Image.h"
#include "Button.h"
#include "Text.h"

#include "TimeOfDayEnum.h"
#include "TimeOfDayIcon.h"

#include "Mission.h"

#include "Timer.h"

#include "Player.h"
#include "PlayerLivesIcon.h"
#include "Enemy.h"
#include "Circle.h"
#include "Wall.h"
#include "Wizard.h"


#include <vector>
#include <array>
#include <optional>
#include <algorithm>

namespace house {

   class Game;

   using namespace GameConstants;

   class Level : public Actor {
      protected:
       Game &m_game;

       bool m_pausable;
       bool m_paused;
       Timer m_pauseDelay;

       const Vector2d<int> m_levelSize;

       static constexpr const char *WallTexturePath = "gfx\\objects\\wall.png";
       SDL_Texture_unique_ptr m_wallTexture;

       const Vector2d<int> m_wallSize;
       std::vector<std::unique_ptr<TiledWall>> m_walls;

       Player &m_player;
       Vector2d<int> m_playerhalfSize;
       std::unique_ptr<PlayerLivesIcon> m_playerLivesIcon;

       std::unique_ptr<Circle> m_circle;

       float m_time;
       int m_secondsPerHour = 12;
       const int HoursPerDay = 24;

       TimeOfDay m_timeOfDay;
       const std::pair<int, int> m_dayDuration {7, 18};
       const std::pair<int, int> m_nightDuration {20, 5};

       TimeOfDayIcon *m_timeOfDayIcon;
       static constexpr const char *DaytimeTooltipInfo    = "It's daytime.\n"
                                           " Enemies do not have any\n"
                                           " buffs during the day, but some\n";

       static constexpr const char *SunsetDawnTooltipInfo = "It's neither day nor night.\n"
                                           " All enemies are buffed,\n"
                                           " try not to die.";

       static constexpr const char *NighttimeTooltipInfo  = "It's nighttime.\n"
                                           " Some enemies may have\n"
                                           " certain buffs and/or debuffs.";
       struct {
         Text *title;
         Button *pause;
         Button *resume;
         Button *exit;
       } m_pauseMenu;
       static constexpr const char *PauseBtnTexturePath  = "gfx\\ui\\menus\\pause.png";
       static constexpr const char *ResumeBtnTexturePath = "gfx\\ui\\menus\\resume.png";
       static constexpr const char *ExitBtnTexturePath   = "gfx\\ui\\menus\\exit.png";
       struct {
         Text *title;
         Text *description;
         Button *exit;
       } m_gameOverScreen;
      
       struct {
         bool draw;
         DrawableObject *object;
         std::unique_ptr<Text> tooltipImage;
       } m_tooltip;

       int m_numberOfEnemies;
       std::vector<std::unique_ptr<Enemy>>  m_enemies;
       std::vector<std::unique_ptr<Actor>>  m_objects;
       std::vector<std::unique_ptr<Button>> m_buttons;
       std::vector<std::unique_ptr<Image>>  m_images;
       std::vector<std::unique_ptr<Text>>   m_texts;

       std::vector<std::unique_ptr<Mission>> m_missions;
       Mission *m_currentMission;
       uint8_t m_numOfMissionAvailable;
       Text *m_currentMissionTitle;
       Text *m_currentMissionDescripion;
       bool m_missionChangeDelayStarted;
       Timer m_missionChangeDelay;

       const std::unique_ptr<Image> m_missionCompleteImage;
       static constexpr const char *MissionCompleteImagePath
                                          = "gfx\\ui\\missionComplete.png";
       static constexpr const char *MissionCompleteSoundPath
                                          = "sfx\\ui\\missionComplete.wav";
       Mix_Chunk_unique_ptr m_missionCompleteSound;

       std::vector<int> m_columnPositions;
       std::vector<int> m_rowPositions;
       bool m_completed;

       void spawn();
       void onSpawn();
       /**
       * \brief Spawns all objects,
       * should be called after every object is added.
       **/
       void startAll();
       void updateAll(float deltaTime);

       void createBoundry();
       void calculateGridPositions();

       virtual void createImages()   = 0;
       virtual void createButtons()  = 0;
       virtual void createWalls()    = 0;
       virtual void createEnemies()  = 0;
       virtual void createObjects()  = 0;
       virtual void createMissions() = 0;

       void handleTimeOfDay(float deltaTime);

       void handleTooltips(const DrawableObject &previousTooltipObject);
       void setTooltipPosition();

       void handleMissions();
       void findNewMission();
       void delayNewMission();

       void handleCollisions();
       void handleObjectsCollisions();
       void handleEnemiesCollisions();
       void handleWallsCollisions();

       virtual void onInput(float deltaTime) = 0;

       void createPauseMenu();
       void openPauseMenu();
       void closePauseMenu();
       void handlePausing();

       void createGameOverScreen();
       void openGameOverScreen();

       virtual void onComplete() = 0;

       void quitToMenu();

       void unloadAll();
       virtual void onUnload() = 0;

       friend void Wizard::shootProjectile(Direction direction);
         
      public:
       Level(Game &game, Camera &camera, Vector2d<int> size,
             const std::string &name = "Level",
             Vector2d<int> startingPosition = CentrePosition);
      
       void load();

       void update(float deltaTime);

       void handleInput(float deltaTime);

       void drawAll();

       void unload();

       std::vector<Actor *> getObjectsInsideCircle();
   };

} // namespace house

#endif // !LEVEL_H