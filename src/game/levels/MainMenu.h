#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "LevelList.h"

#include "Level.h"

namespace house {

    class MainMenu : public Level {
        private:
         static constexpr const char *TitleLogoTexturePath
                                            = "gfx\\ui\\menus\\title.png";
         static constexpr const char *StartGameTexturePath
                                            = "gfx\\ui\\menus\\gameStart.png";
         static constexpr const char *ExitGameTexturePath
                                            = "gfx\\ui\\menus\\gameExit.png";
         static constexpr const char *TutorialTexturePath
                                            = "gfx\\ui\\menus\\tutorial.png";
         
         void onInput(float deltaTime);

         void createImages();
         void createButtons();
         void createWalls();
         void createEnemies();
         void createObjects();
         void createMissions();

        public:
         MainMenu(Game &game, Camera &camera);

         void onStart();
         void onUpdate(float deltaTime);

         void onComplete();
        
         void onCollision(const Actor &other);

         void startGame();
         void startTutorial();
         void quitGame();

         void onUnload();
    };
    
} // namespace house

#endif // !MAIN_MENU_H