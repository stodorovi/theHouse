#include "TutorialLevel.h"

namespace house {
    
    TutorialLevel::TutorialLevel(Game &game, Camera &camera)
    : Level(game, camera, LevelSize, "Tutorial"),
    m_firstBarrier{nullptr}, m_secondBarrier{nullptr},
    m_constTime{12}
    {}

    void TutorialLevel::onStart() {

        createFirstBarier();
        createEnemies();
        createMissions();

        startAll();

        m_player.setPosition({static_cast<float>((-m_levelSize.w / 2) +
                              m_player.getSize().w), 0});

        // look to the right so it doesn't autocomplete the first mission
        m_player.animatedFollow(0, *m_enemies[0]);

        m_camera.setPosition(m_player.getPosition());

        m_constTime = 12;
    }

    void TutorialLevel::onUpdate(float deltaTime) {
        m_time = m_constTime;
    }

    void TutorialLevel::onInput(float deltaTime) {

    }

    void TutorialLevel::onComplete() {

    }

    void TutorialLevel::onCollision(const Actor &other) {

    }

    void TutorialLevel::onUnload() {

    }

    void TutorialLevel::createImages() {

    }

    void TutorialLevel::createButtons() {

    }

    void TutorialLevel::createWalls() {

    }

    void TutorialLevel::createEnemies() {
        m_enemies.emplace_back (std::make_unique<DummySoldier>(this, m_camera));
        
        
        m_enemies.emplace_back (std::make_unique<DummySoldier>(this, m_camera));
        Vector2d<int> pos = {m_columnPositions[26], m_rowPositions[3]};
        m_enemies.back()->setPosition(pos);
    }

    void TutorialLevel::createObjects() {

    }

    void TutorialLevel::createMissions() {
        m_missions.emplace_back(std::make_unique<Mission>(
                                   "GO LEFT!",
                                   [&]() {
                                       return (m_player.getFacingDirection() ==
                                               Direction::Left);
                                   },
                                   [](){},
                                   "Press 'a'\n"
                                   " to go left.")
        );

        m_missions.emplace_back(std::make_unique<Mission>(
                                   "GO RIGHT!",
                                   [&]() {
                                       return (m_player.getFacingDirection() ==
                                               Direction::Right);
                                   },
                                   [](){},
                                   "Press 'd'\n"
                                   " to go right.")
        );

        m_missions.emplace_back(std::make_unique<Mission>(
                                   "GO UP!",
                                   [&]() {
                                       return (m_player.getFacingDirection() ==
                                               Direction::Up);
                                   },
                                   [](){},
                                   "Press 'w'\n"
                                   " to go up.")
        );

        m_missions.emplace_back(std::make_unique<Mission>(
                                   "GO DOWN!", [&]() {
                                       return (m_player.getFacingDirection() ==
                                               Direction::Down);
                                   },
                                   [](){},
                                   "Press 's'\n"
                                   " to go down.")
        );
        
        m_missions.emplace_back(std::make_unique<Mission>(
                                   "ATTACK!",
                                   [&]() {
                                       return (m_player.getCurrentAction() ==
                                               Action::Attacking);
                                },
                                [](){},
                                "Press 'LCtrl'\n"
                                " to attack")
        );

        m_missions.emplace_back(std::make_unique<Mission>(
                                   "DEFEND!", [&]() {
                                       return (m_player.getCurrentAction() ==
                                               Action::Defending);
                                   },
                                   [](){},
                                   "Press 'Alt'\n"
                                   " to defend")
        );

        m_missions.emplace_back(std::make_unique<Mission>(
                                   "TOOLTIP!",
                                   [&]() {
                                       return m_player.isMouseOver();
                                   },
                                   std::bind(&TutorialLevel::tooltipTutorial,
                                              this),
                                   "Hover over\n"
                                   " yourself to\n"
                                   " find some useful\n"
                                   " information.\n"
                                   "You will find that\n"
                                   " most things, such\n"
                                   " as the enemies,\n"
                                   " have info that\n"
                                   " might help you.")
        );

        m_missions.emplace_back(std::make_unique<Mission>(
                                  "APPROACH\nTHE ENEMY!",
                                  [&]() {
                                      return m_player.isCollidingWith(
                                                               *m_enemies[0]);
                                   },
                                   std::bind(
                                       &TutorialLevel::enemyApproachTutorial,
                                        this
                                   ),
                                   "There is an\n"
                                   " enemy ahead.\n"
                                   " Approach him.")
        );

        m_missions.emplace_back(std::make_unique<Mission>(
                                   "ATTACK\nTHE ENEMY!",
                                   [&]() {
                                       return (
                                           m_player.isCollidingWith(
                                                            *m_enemies[0]) &&
                                           m_player.getCurrentAction() ==
                                                            Action::Attacking
                                       );
                                   },
                                   std::bind(
                                       &TutorialLevel::enemyDefenseTutorial,
                                        this
                                   ),
                                   "The enemy\n "
                                   " attacked you.\n"
                                   "Take your\n"
                                   " revenge.")
        );

        m_missions.emplace_back(std::make_unique<Mission>(
                                   "KILL\nTHE ENEMY!",
                                   [&]() {
                                       return (m_enemies[0]->getHealth() == 0);
                                   },
                                   std::bind(&TutorialLevel::enemyKillTutorial,
                                              this),
                                   "You can not\n"
                                   " kill an enemy\n"
                                   " who is defending.\n"
                                   " Try and kill\n"
                                   " the enemy when\n"
                                   " he is not\n"
                                   " defending or\n"
                                   " approach him\n"
                                   " from the rear.\n"
                                   "\n \nREWARD:\n"
                                   " +0.5 HP")
        );
                                
        m_missions.emplace_back(std::make_unique<Mission>(
                                   "THE NIGHT!",
                                   [&]() {
                                       return (m_enemies[1]->getHealth() == 0);
                                   },
                                   [](){},
                                   "It is nighttime.\n"
                                   "The enemy ahead\n"
                                   " is twice as\n"
                                   " powerful, so\n"
                                   " you will need\n"
                                   " to hit him\n"
                                   " twice to kill\n"
                                   " him, but he\n"
                                   " can also deal\n"
                                   " twice the damage.")
        );
                                
        m_missions.emplace_back(std::make_unique<Mission>(
                                   "THE END\nOF THE\nTUTORIAL!",
                                   [](){
                                       return false;
                                   },
                                   [](){},
                                   "This is the\n"
                                   " end of the\n"
                                   " tutorial.\n"
                                   "Start the game\n"
                                   " and apply your \n"
                                   " newly acquired\n"
                                   " knowledge.\n")
        );
    }

    void TutorialLevel::createFirstBarier() {
        for (int i = 0; i < m_firstBarrier.size(); ++i) {
            auto pos = Vector2d<int>{m_columnPositions[7], m_rowPositions[i]};

            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(m_camera,
                                                              pos,
                                                              m_wallSize)
                                )
            );            
            m_firstBarrier[i] = dynamic_cast<TiledWall*>(m_walls.back().get());
        }
    }

    void TutorialLevel::spawnFirstBarier() {
        for (auto wall : m_firstBarrier) {
            wall->spawn();
        }
    }
    void TutorialLevel::despawnFirstBarier() {
        for (auto wall : m_firstBarrier) {
            wall->despawn();
        }
    }

    void TutorialLevel::createSecondBarier() {
        for (int i = 0; i < m_secondBarrier.size(); ++i) {
            auto pos = Vector2d<int>{m_columnPositions[16], m_rowPositions[i]};

            m_walls.emplace_back(std::move(
                                  std::make_unique<TiledWall>(m_camera,
                                                              pos,
                                                              m_wallSize)
                                )
            );            
            m_secondBarrier[i] = dynamic_cast<TiledWall*>(
                                                    m_walls.back().get());
        }
    }
    void TutorialLevel::spawnSecondBarier() {
        for (auto wall : m_secondBarrier) {
            wall->spawn();
        }
    }
    void TutorialLevel::despawnSecondBarier() {
        for (auto wall : m_secondBarrier) {
            wall->despawn();
        }
    }

    void TutorialLevel::spawnFirstAndSecondBarrier() {
        spawnFirstBarier();
        spawnSecondBarier();
    }
    void TutorialLevel::despawnFirstAndSecondBarrier() {
        despawnFirstBarier();
        despawnSecondBarier();
    }

    void TutorialLevel::tooltipTutorial() {
        despawnFirstBarier();

        if (m_secondBarrier.size() != 0) {
            createSecondBarier();
        }
        spawnSecondBarier();
    }

    void TutorialLevel::enemyApproachTutorial() {
        spawnFirstAndSecondBarrier();

        auto &enemy = dynamic_cast<DummySoldier&>(*m_enemies[0]);
        enemy.tutorialAttack();
    }
    void TutorialLevel::enemyDefenseTutorial() {
        dynamic_cast<DummySoldier&>(*m_enemies[0]).tutorialDefend();
    }
    void TutorialLevel::enemyKillTutorial() {
        despawnFirstAndSecondBarrier();

        m_player.setHealth(m_player.getHealth() + 1);
        m_constTime = 0;

        despawnSecondBarier();
    }

} // namespace house