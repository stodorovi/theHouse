#ifndef GAME_H
#define GAME_H

#include <string>
#include <unordered_map>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Vector2d.h"
#include "SDLSmartPtrs.h"
#include "gameConstants.h"
#include "LevelList.h"

#include "Camera.h"
#include "MainMenu.h"
#include "Level_One.h"
#include "TutorialLevel.h"

#include "GameException.h"

namespace house {

    class Game {
        private:
        const std::string m_Title;

        bool m_isRunning;

        SDL_Window_unique_ptr m_window;
        std::unique_ptr<Camera> m_camera;

        SDL_Event m_event;

        std::unique_ptr<Player> m_player;
        
        std::unordered_map<LevelList, std::unique_ptr<Level>> m_levels;
        Level *m_currentLevel;

        float m_deltaTime;
        int m_frameRate;

    public:
     Game(const std::string &title);
     ~Game() = default;

     int init();
     void start();
     void unload() noexcept;

     const bool isRunning() const noexcept;

     Player& getPlayer() const;

     void quit();
     void changeLevel(LevelList level);

    private:
     void handleInput();
     void update();
     void draw();
    };

} // namespace house

#endif // !GAME_H