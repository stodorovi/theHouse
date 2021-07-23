#include "MainMenu.h"
#include "Game.h"
#include "Character.h"

namespace house {
    
    MainMenu::MainMenu(Game &game, Camera &camera)
    : Level(game, camera, {0, 0}, "Main Menu")
    {
        m_secondsPerHour = 1;
        m_pausable = false;
    }

    void MainMenu::onStart() {
        
        createButtons();
        createImages();

        startAll();
        
        m_player.setHealth(Character::DefaultNumberOfLives);
        m_player.despawn();
        m_playerLivesIcon->despawn();


        // position time of day icon to centre
        auto newPosition = GameConstants::UICentrePosition;
        newPosition -= {0, 30};
        m_timeOfDayIcon->setPosition(newPosition);
        m_timeOfDayIcon->scale(2.5f);
    }
    
    void MainMenu::onUpdate(float deltaTime) {
        
    }

    void MainMenu::onComplete() {
        
    }
    
    void MainMenu::onInput(float deltaTime) {
        
    }

    void MainMenu::onCollision(const Actor &other) {

    }

    void MainMenu::startGame() {
        m_game.changeLevel(LevelList::LevelOne);
    }
    
    void MainMenu::startTutorial() {
        m_game.changeLevel(LevelList::Tutorial);
    }

    void MainMenu::quitGame() {
        m_game.quit();
    }

    void MainMenu::onUnload() {
        
    }

    void MainMenu::createImages() {
        m_images.emplace_back(std::move(
                               std::make_unique<Image>(
                                        TitleLogoTexturePath,
                                        m_camera, "Title logo",
                                        Vector2d<int>{
                                            GameConstants::UICentrePosition.x,
                                            140
                                        })
                              )
        );
    }

    void MainMenu::createButtons() {
        m_buttons.emplace_back(std::move(std::make_unique<Button>(
                                                    StartGameTexturePath,
                                                    m_camera, "Start game",
                                                    Vector2d<int>{15, 36})));
        m_buttons.back()->connectOnClick(std::bind(&MainMenu::startGame,
                                                    this));

        m_buttons.emplace_back(std::move(std::make_unique<Button>(
                                                    ExitGameTexturePath,
                                                    m_camera, "Exit game",
                                                    Vector2d<int>{7, 78})));
        m_buttons.back()->connectOnClick(std::bind(&MainMenu::quitGame, this));

        m_buttons.emplace_back(std::move(
                                std::make_unique<Button>(
                                        TutorialTexturePath,
                                        m_camera, "Start Tutorial",
                                        Vector2d<int>{
                                            GameConstants::UICentrePosition.x +
                                             (GameConstants::CircleSize.w /
                                              2) - 3,
                                            GameConstants::UICentrePosition.y -
                                             15})
                               )
        );
        m_buttons.back()->connectOnClick(std::bind(&MainMenu::startTutorial,
                                                    this));
    }

    void MainMenu::createWalls() {

    }

    void MainMenu::createEnemies() {

    }
    void MainMenu::createObjects() {

    }

    void MainMenu::createMissions() {

    }
    
} // namespace house