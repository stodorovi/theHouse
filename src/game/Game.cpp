#include "Game.h"

namespace house {
    
    Game::Game(const std::string &title)
    :m_Title{title}, m_isRunning{false},
    m_window{nullptr}, m_camera {nullptr},
    m_event{0}, m_player{nullptr},
    m_currentLevel{nullptr},
    m_deltaTime{0.0f}, m_frameRate{0}
    {}

    int Game::init() {
        std::string errorMessage;
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) errorMessage = SDL_GetError();
        if (!errorMessage.empty()) throw GameException(errorMessage);

        if (IMG_Init(IMG_INIT_PNG) == 0) errorMessage = IMG_GetError();
        if (!errorMessage.empty()) throw GameException(errorMessage);

        if (TTF_Init() <0) errorMessage = TTF_GetError();
        if (!errorMessage.empty()) throw GameException(errorMessage);

        SDL_DisplayMode displayMode;
        if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0) {
            errorMessage = SDL_GetError();
        }
        if (!errorMessage.empty()) throw GameException(errorMessage);

        m_window.reset(SDL_CreateWindow(std::string(m_Title).c_str(),
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        displayMode.w, displayMode.h,
                                        SDL_WINDOW_SHOWN |
                                        SDL_WINDOW_BORDERLESS));
        if (m_window == nullptr) errorMessage = SDL_GetError();
        if (!errorMessage.empty()) throw GameException(errorMessage);

        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT,
                          MIX_CHANNELS, 2048) == -1) {
            errorMessage = Mix_GetError();
        }
        if (!errorMessage.empty()) throw GameException(errorMessage);


        m_camera = std::move(
                    std::make_unique<Camera>(*m_window,
                                             GameConstants::BackgroundColour));
        m_camera->spawn();
        
        m_player = std::move(
                    std::make_unique<Player>(nullptr, *m_camera));

        m_levels.emplace(LevelList::MainMenu,
                         std::move(
                          std::make_unique<MainMenu>(*this, *m_camera)));
        m_currentLevel = m_levels[LevelList::MainMenu].get();

        m_levels.emplace(LevelList::LevelOne,
                         std::move(
                          std::make_unique<LevelOne>(*this, *m_camera)));

        m_levels.emplace(LevelList::Tutorial,
                         std::move(
                          std::make_unique<TutorialLevel>(*this, *m_camera)));

        m_isRunning = true;

        return true;
   }

    void Game::start() {
        float beginFrameTime = 0.0f;
        float endFrameTime = 0.0f;

        m_camera->start();
        try {
            m_currentLevel->load();
        }
        catch (GameException &e) {
            throw e;
        }

        while (m_isRunning) {
            beginFrameTime = endFrameTime;

            handleInput();
            update();
            draw();

            endFrameTime = static_cast<float>(SDL_GetTicks()) / 1000;
            m_deltaTime = endFrameTime - beginFrameTime;
            m_frameRate = static_cast<int>(1 / m_deltaTime);
        }
    }

    void Game::handleInput() {
        while (SDL_PollEvent(&m_event)) {
            switch (m_event.type) {
                default:
                    break;
            }
        }
       
        m_currentLevel->handleInput(m_deltaTime);
    }

    void Game::update() {
        m_currentLevel->update(m_deltaTime);
    }

    void Game::draw() {
        m_camera->clear();
        m_currentLevel->drawAll();
        m_camera->present();
    }

    const bool Game::isRunning() const noexcept { return m_isRunning; }

    Player& Game::getPlayer() const { return *m_player; }

    void Game::changeLevel(LevelList level) {
        m_currentLevel->unload();
        m_currentLevel = m_levels[level].get();
        m_player->m_level = m_currentLevel;
        m_currentLevel->load();
    }

    void Game::quit() { m_isRunning = false; }

    void Game::unload() noexcept {
        IMG_Quit();
        SDL_Quit();
    }
    
} // namespace house