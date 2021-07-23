#include "Level_One.h"

namespace house {

    LevelOne::LevelOne(Game &game, Camera &camera)
    : Level(game, camera, LevelSize, Name),
        m_firstMissionWizard{nullptr}, m_firstMissionSoldier{nullptr},
        m_firstMissionLockedDoor{nullptr}, m_secondMissionLockedDoor{nullptr},
        m_secondMissionKey{nullptr}
    {}

    void LevelOne::onStart() {
        m_pausable = true;
        m_secondsPerHour = 2;

        createWalls();
        createEnemies();
        createObjects();
        createMissions();
        
        startAll();

        Vector2d<int> playerSpawnPoint{m_columnPositions[2],
                                       m_rowPositions[19]};
        m_player.setPosition(playerSpawnPoint);
        m_camera.setPosition(playerSpawnPoint);
    }

    void LevelOne::onUpdate(float deltaTime) {

    }

    void LevelOne::onInput(float deltaTime) {

    }

    void LevelOne::onComplete() {

    }

    void LevelOne::onCollision(const Actor &other) {

    }

    void LevelOne::onUnload() {
        m_firstMissionWizard      = nullptr;
        m_firstMissionSoldier     = nullptr;
        m_firstMissionLockedDoor  = nullptr;
        m_secondMissionLockedDoor = nullptr;
        m_secondMissionKey        = nullptr;
    }

    void LevelOne::createImages() {

    }
    void LevelOne::createButtons() {

    }

    void LevelOne::createWalls() {
        
    // 1. row
        m_walls.emplace_back(std::move(
                              std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[1],
                                                        m_rowPositions[0]},
                                                    m_wallSize)
                            )
        );
        
    // 2. row
        for (int i = 1; i < 26; ++i) {
            if (i == 2) continue;

            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[1]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 3. row
        std::array<int, 2> rowThreeWalls{1, 25};
        for (int &i : rowThreeWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[2]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 4. row
        for (int i = 1; i < 26; ++i) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[3]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 5. row
        m_walls.emplace_back(std::move(
                              std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[1],
                                                        m_rowPositions[4]},
                                                    m_wallSize)
                            )
        );
        
    // 6. row
        for (int i = 1; i < 26; ++i) {
            if (i == 2 || i == 8 || i == 18) continue;

            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[5]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 7. row
        std::array<int, 6> rowSevenWalls{1, 3, 9, 17, 19, 25};
        for (int &i : rowSevenWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[6]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 8. row
        std::array<int, 12> rowEightWalls{1, 3, 9, 11, 12, 13,
                                          14, 15, 16, 17, 19, 25};
        for (int &i : rowEightWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[7]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 9. row
        std::array<int, 4> rowNineWalls{1, 3, 9, 19};
        for (int &i : rowNineWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[8]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 10. row
        for (int i = 1; i <= 19; ++i) {
            if (i == 2 || i == 14) continue;

            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[9]},
                                                    m_wallSize)
                                )
            );
        }
        std::array<int, 4> rowElevenWalls{1, 9, 19, 25};
        for (int &i : rowElevenWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[10]},
                                                    m_wallSize)
                                )
        );
        }
        
    // 12. row
        for (int i = 1; i <= 25; ++i) {
            if (i == 2 || i == 8 || (i > 9 && i < 19)) continue;

            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[11]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 13. row
        std::array<int, 6> rowThirteenlWalls{1, 3, 7, 9, 19, 25};
        for (int &i : rowThirteenlWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[12]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 14.row
        std::array<int, 11> rowFourteenWalls{1, 3, 4, 5, 7, 21, 22, 23, 25};
        for (int &i : rowFourteenWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[13]},
                                                    m_wallSize)
                                )
            );
        }                                                              
        
    // 15. row
        std::array<int, 6> rowFifteenWalls{1, 7, 21, 23};
        for (int &i : rowFifteenWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[14]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 16. row
        std::array<int, 11> rowSixteenWalls{1, 2, 3, 4, 5, 6,
                                            7, 9, 19, 21, 23};
        for (int &i : rowSixteenWalls) {
            if (i == 8 || i == 20 || i == 22) continue;
            
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[15]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 17. row
        std::array<int, 4> rowSeventeenWalls{9, 19, 21, 23};
        for (int &i : rowSeventeenWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[16]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 18. row
        for (int i = 0; i <= 23; ++i) {
            if (i == 20 || i == 22 || (i > 9 && i < 19)) continue;

            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[17]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 19. row
        std::array<int, 5> rowNineteenWalls{5, 9, 19, 21, 23};
        for (int &i : rowNineteenWalls) {
            m_walls.emplace_back(std::move(
                                 std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[18]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 20. row
        for (int i = 7; i <= 26; ++i) {
            if (i == 8 || i == 14 || i == 20 || i == 22) continue;

            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[19]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 21. row
        std::array<int, 4> rowTwentyOneWalls{7, 9, 19, 21};
        for (int &i : rowTwentyOneWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[20]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 22. row
        for (int i = 0; i <= 25; ++i) {
            if (i == 4 || i == 6 || i == 8 || i == 12 ||
                i == 16 || i == 20 || i == 24)
            {
                continue;
            }

            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[21]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 23. row
        std::array<int, 10> rowTwentyThreeWalls{1, 5, 7, 9, 11,
                                                13, 15, 17, 23, 25};
        for (int &i : rowTwentyThreeWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[22]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 24. row
        std::array<int, 11> rowTwentyFourWalls{1, 5, 7, 9, 10, 11,
                                               13, 15, 17, 23, 25};
        for (int &i : rowTwentyThreeWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[23]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 25. row
        std::array<int, 7> rowTwentyFiveWalls{1, 5, 7, 13, 17, 23, 25};
        for (int &i : rowTwentyFiveWalls) {
            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[24]},
                                                    m_wallSize)
                                )
            );
        }
        
    // 26. row
        for (int i = 5; i <= 16; ++i) {
            if (i == 6) continue;

            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[25]},
                                                    m_wallSize)
                                )
            );
        }
        std::array<int, 2> rowTwentySixAdditionalWalls{24, 25};
        for (int &i : rowTwentySixAdditionalWalls) {
                m_walls.emplace_back(std::move(
                                      std::make_unique<TiledWall>(
                                                    m_camera,
                                                    Vector2d<int>{
                                                        m_columnPositions[i],
                                                        m_rowPositions[25]},
                                                    m_wallSize)
                                    )
                );
        }
        
    // 27. row
        m_walls.emplace_back(std::move(
                              std::make_unique<TiledWall>(
                                                m_camera,
                                                Vector2d<int>{
                                                    m_columnPositions[5],
                                                    m_rowPositions[26]},
                                                m_wallSize)
                            )
        );
    }

    void LevelOne::createEnemies() {
        using v2Di = Vector2d<int>;
        auto &GridXPos = m_columnPositions;
        auto &GridYPos = m_rowPositions;
        
        std::array<v2Di, 27> soldiersPositions {
            v2Di{GridXPos[ 0], GridYPos[ 0]}, v2Di{GridXPos[16], GridYPos[ 0]},
            v2Di{GridXPos[13], GridYPos[ 2]}, v2Di{GridXPos[ 2], GridYPos[ 4]},
            v2Di{GridXPos[20], GridYPos[ 4]}, v2Di{GridXPos[15], GridYPos[ 6]},
            v2Di{GridXPos[ 0], GridYPos[ 6]}, v2Di{GridXPos[ 0], GridYPos[ 9]},
            v2Di{GridXPos[ 6], GridYPos[ 7]}, v2Di{GridXPos[22], GridYPos[ 7]},
            v2Di{GridXPos[22], GridYPos[ 9]}, v2Di{GridXPos[ 8], GridYPos[10]},
            v2Di{GridXPos[ 4], GridYPos[12]}, v2Di{GridXPos[20], GridYPos[15]},
            v2Di{GridXPos[ 1], GridYPos[16]}, v2Di{GridXPos[24], GridYPos[16]},
            v2Di{GridXPos[25], GridYPos[16]}, v2Di{GridXPos[26], GridYPos[16]},
            v2Di{GridXPos[ 8], GridYPos[20]}, v2Di{GridXPos[10], GridYPos[20]},
            v2Di{GridXPos[16], GridYPos[20]}, v2Di{GridXPos[19], GridYPos[23]},
            v2Di{GridXPos[24], GridYPos[24]}, v2Di{GridXPos[ 6], GridYPos[26]},
            v2Di{GridXPos[19], GridYPos[26]}, v2Di{GridXPos[16], GridYPos[26]},
            v2Di{GridXPos[ 0], GridYPos[22]}
        };

        for (auto &pos : soldiersPositions) {
            m_enemies.emplace_back(std::move(
                                    std::make_unique<Soldier>(this, m_camera,
                                                              pos)));
        }
        m_firstMissionSoldier = static_cast<Soldier*>(m_enemies.back().get());

        std::array<v2Di, 3> wizardsPositions {
            v2Di{GridXPos[14], GridYPos[14]},
            v2Di{GridXPos[13], GridYPos[14]},
            v2Di{GridXPos[ 3], GridYPos[23]}, 
        };
        for (auto &pos : wizardsPositions) {
            m_enemies.emplace_back(std::move(
                                    std::make_unique<Wizard>(this, m_camera,
                                                             pos)));
        }
        m_firstMissionWizard = static_cast<Wizard*>(m_enemies.back().get());
    }

    void LevelOne::createObjects() {
        auto vertical = Orientation::Vertical;
        std::array<Vector2d<int>, 5> verticalDoorPositions {
            Vector2d<int>{m_columnPositions[25], m_rowPositions[ 8]},
            Vector2d<int>{m_columnPositions[ 9], m_rowPositions[13]},
            Vector2d<int>{m_columnPositions[19], m_rowPositions[13]},
            Vector2d<int>{m_columnPositions[ 1], m_rowPositions[25]},
            Vector2d<int>{m_columnPositions[17], m_rowPositions[25]},
        };
        for (auto& pos : verticalDoorPositions) {
            m_objects.emplace_back(std::move(
                                    std::make_unique<Door>(m_camera, pos,
                                                           vertical)));
        }

        auto horizontal = Orientation::Horizontal;
        std::array<Vector2d<int>, 9> horizontalDoorPositions {
            Vector2d<int>{m_columnPositions[ 8], m_rowPositions[ 5]},
            Vector2d<int>{m_columnPositions[13], m_rowPositions[ 9]},
            Vector2d<int>{m_columnPositions[ 5], m_rowPositions[10]},
            Vector2d<int>{m_columnPositions[24], m_rowPositions[13]},
            Vector2d<int>{m_columnPositions[26], m_rowPositions[13]},
            Vector2d<int>{m_columnPositions[14], m_rowPositions[ 9]},
            Vector2d<int>{m_columnPositions[14], m_rowPositions[19]},
            Vector2d<int>{m_columnPositions[ 4], m_rowPositions[21]},
            Vector2d<int>{m_columnPositions[20], m_rowPositions[21]},
        };
        for (auto& pos : horizontalDoorPositions) {
            m_objects.emplace_back(std::move(
                                    std::make_unique<Door>(m_camera, pos,
                                                           horizontal)));
        }

        auto pos = Vector2d<int>{m_columnPositions[5], m_rowPositions[19]};
        m_objects.emplace_back(std::move(
                                std::make_unique<LockedDoor>(m_camera, pos,
                                                             vertical)));
        m_firstMissionLockedDoor
                            = static_cast<LockedDoor*>(m_objects.back().get());

        pos = {m_columnPositions[23], m_rowPositions[25]};
        m_objects.emplace_back(std::move(
                                std::make_unique<LockedDoor>(m_camera, pos,
                                                             vertical)));
        m_secondMissionLockedDoor
                            = static_cast<LockedDoor*>(m_objects.back().get());

        pos = {m_columnPositions[24], m_rowPositions[2]};
        m_objects.emplace_back(std::move(
                                std::make_unique<Key>(m_camera, pos)));
        m_secondMissionKey = static_cast<Key*>(m_objects.back().get());

        pos = {m_columnPositions[22], m_rowPositions[14]};
        m_objects.emplace_back(std::move(
                                std::make_unique<LevelExit>(m_camera, pos)));
        m_levelExit = static_cast<LevelExit*>(m_objects.back().get());
    }

    void LevelOne::createMissions() {
        m_missions.emplace_back(std::move(
                                 std::make_unique<Mission>(
                                      m_firstMissionTitle,
                                      std::bind(
                                          &LevelOne::firstMissionCondition,
                                           this),
                                      std::bind(
                                          &LevelOne::firstMissiononCompletion,
                                           this),
                                      m_firstMissionDescription)));

        m_missions.emplace_back(std::move(
                                 std::make_unique<Mission>(
                                      m_secondMissionTitle,
                                      std::bind(
                                          &LevelOne::secondMissionCondition,
                                           this),
                                      std::bind(
                                          &LevelOne::secondMissiononCompletion,
                                           this),
                                      m_secondMissionDescription)));

        m_missions.emplace_back(std::move(
                                 std::make_unique<Mission>(
                                      m_thirdMissionTitle,
                                      std::bind(
                                          &LevelOne::thirdMissionCondition,
                                           this),
                                      std::bind(
                                          &LevelOne::thirdMissiononCompletion,
                                           this),
                                      m_thirdMissionDescription)));
    }

    bool LevelOne::firstMissionCondition() {
        return (m_firstMissionSoldier->isActive() == false &&
                m_firstMissionWizard->isActive() == false);
    }
    void LevelOne::firstMissiononCompletion() {
        m_firstMissionLockedDoor->despawn();
        m_player.setHealth(m_player.getHealth() + 2);
    }

    bool LevelOne::secondMissionCondition() {
        return (m_secondMissionKey->isActive() == false);
    }
    void LevelOne::secondMissiononCompletion() {
        m_secondMissionLockedDoor->despawn();
        m_player.setHealth(m_player.getHealth() + 4);
    }

    bool LevelOne::thirdMissionCondition() {
        return (m_player.isCollidingWith(*m_levelExit));
    }
    void LevelOne::thirdMissiononCompletion() {
        m_game.changeLevel(LevelList::MainMenu);
    }

} // namespace house