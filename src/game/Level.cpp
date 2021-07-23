#include "Level.h"
#include "game/Game.h"

namespace house {
    
    Level::Level(Game &game, Camera &camera, Vector2d<int> size,
                 const std::string &name,
                 Vector2d<int> startingPosition)
    : Actor(camera, name, startingPosition),
    m_game{game}, m_pausable{true}, m_paused{false},
    m_pauseDelay{Timer(200)}, m_levelSize{size},
    m_wallTexture{nullptr}, m_wallSize{16, 16},
    m_player{m_game.getPlayer()}, m_playerhalfSize {0, 0},
    m_playerLivesIcon{nullptr},
    m_circle {nullptr}, m_time{0}, m_timeOfDay{TimeOfDay::Night},
    m_timeOfDayIcon {nullptr},
    m_pauseMenu{nullptr, nullptr, nullptr, nullptr},
    m_gameOverScreen{nullptr, nullptr, nullptr},
    m_tooltip{false, nullptr, nullptr},
    m_numberOfEnemies{0}, m_currentMission{nullptr},
    m_numOfMissionAvailable{UINT8_MAX},
    m_currentMissionTitle{nullptr}, m_currentMissionDescripion{nullptr},
    m_missionChangeDelay{500}, m_missionChangeDelayStarted{false},
    m_missionCompleteImage{
        std::make_unique<Image>(MissionCompleteImagePath, camera,
                                "Mission Complete")
    },
    m_missionCompleteSound{
        AudioManager::loadAudioWav(MissionCompleteSoundPath)
    },
    m_completed{false}
    {}

    void Level::spawn() {
        onSpawn();
        activate();
        calculateGridPositions();
    }
    void Level::onSpawn() {
        m_wallTexture.reset(TextureManager::loadTexture(&m_camera.getRenderer(),
                                                        WallTexturePath));

        m_missionCompleteImage->spawn();
        m_missionCompleteImage->deactivate();
   }

    void Level::startAll() {
        m_circle = std::move(std::make_unique<Circle>(m_camera));
        m_playerLivesIcon = std::move(
                             std::make_unique<PlayerLivesIcon>(
                                            m_camera,
                                            "These are your lives. "
                                            "Avoid losing them all.")
                            );
        // level title
        m_texts.emplace_back(std::move(
                              std::make_unique<Text>(
                                            m_camera,
                                            m_name,
                                            Vector2d<int>{UICentrePosition.x,
                                                          10},
                                            AlignSide::Right |
                                            AlignSide::VerticalCentre)
                            )
        );

        m_texts.emplace_back(std::move(
                              std::make_unique<Text>(
                                            m_camera, "",
                                            Vector2d<int>{UICentrePosition.x +
                                                          (CircleSize.x / 2),
                                                         75},
                                            AlignSide::Down | AlignSide::Left,
                                            14, DefaultFont)
                            )
        );
        m_currentMissionTitle = m_texts.back().get();

        m_texts.emplace_back(std::move(
                              std::make_unique<Text>(
                                            m_camera, "",
                                            Vector2d<int>{UICentrePosition.x +
                                                          (CircleSize.x / 2) +
                                                           5,
                                                          75},
                                            AlignSide::Up | AlignSide::Left,
                                            8, DescriptionFont)
                            )
        );
        m_currentMissionDescripion = m_texts.back().get();

        m_images.emplace_back(std::move(
                               std::make_unique<TimeOfDayIcon>(m_camera)));
        m_timeOfDayIcon = dynamic_cast<TimeOfDayIcon*>(m_images.back().get());

        m_player.spawn();
        m_player.start();
        m_playerhalfSize = m_player.getSize() / 2;
        m_playerLivesIcon->spawn();
        m_playerLivesIcon->start();
        m_camera.setPosition(m_player.getPosition());


        m_circle->spawn();
        m_circle->start();
        m_circle->setColliderSize(CircleSize + m_playerhalfSize);

        if (m_pausable) {
            createPauseMenu();
            createGameOverScreen();
        }

        createBoundry();
        for (auto &wall : m_walls) {
            wall->spawn();
        }

        for (auto &enemy : m_enemies) {
            enemy->spawn();
            enemy->start();
        }
        for (auto &object : m_objects) {
            object->spawn();
            object->start();
        }
        for (auto &button : m_buttons) {
            button->spawn();
             button->start();
       }
        for (auto &image : m_images) {
            image->spawn();
            image->start();
        }
        for (auto &text : m_texts) {
            text->spawn();
            text->start();
        }

        m_time = 12;

        // setting wrong time of day to to trigger time of day change
        // thus setting the tooltip text
        m_timeOfDay = TimeOfDay::Night;

        m_tooltip.object = nullptr;
    }

    void Level::update(float deltaTime) {
        int beginPlayerHP = m_player.getHealth();

        updateAll(deltaTime);
        handleCollisions();
        handleTimeOfDay(deltaTime);
        onUpdate(deltaTime);
        m_camera.follow(deltaTime, m_player, 40);

        int endPlayerHP = m_player.getHealth();
        if (endPlayerHP != beginPlayerHP &&
           endPlayerHP <= 0 &&
           beginPlayerHP > 0)
        {
            openGameOverScreen();
        }
    }

    void Level::updateAll(float deltaTime) {
        handleInput(deltaTime);

        auto previousTooltipObject = m_tooltip.object;
        m_tooltip.object = nullptr;
        m_tooltip.draw = false;

        if (!m_paused) {
            if (m_player.isActive()) {
                m_player.update(deltaTime);
                if (m_player.isMouseOver() && m_tooltip.object != &m_player) {
                    m_tooltip.object = &m_player;
                }
            }

            if (m_playerLivesIcon->isActive()) {
                m_playerLivesIcon->setLives(m_player.getHealth());
                if (m_playerLivesIcon->isMouseOver() &&
                    m_tooltip.object != m_playerLivesIcon.get())
                {
                    m_tooltip.object = m_playerLivesIcon.get();
                }
            }

            if (m_circle->isActive()) m_circle->update(deltaTime);
            
            m_numberOfEnemies = 0;
            for (auto &enemy : m_enemies) {
                if (enemy->isActive() &&
                    enemy->isCollidingWith(m_circle->getCollider()))
                {
                    enemy->update(deltaTime, m_player);
                    m_numberOfEnemies += static_cast<int>(enemy->getType() ==
                                                          ObjectType::Enemy);
                    if (enemy->isMouseOver() &&
                        m_tooltip.object != enemy.get() &&
                        enemy->isCollidingWith(m_circle->getCollider()))
                    {
                        m_tooltip.object = enemy.get();
                    }
                }
            }

            for (auto &object : m_objects) {
                if (object->isActive() &&
                    object->isCollidingWith(m_circle->getCollider()))
                {
                    object->update(deltaTime);
                    if (object->isMouseOver() &&
                        m_tooltip.object != object.get() &&
                        object->isCollidingWith(m_circle->getCollider()))
                    {
                        m_tooltip.object = object.get();
                    }
                }
            }

            for (auto &image : m_images) {
                if (image->isActive()) {
                    image->update(deltaTime);
                    if (image->isMouseOver() &&
                        m_tooltip.object != image.get())
                    {
                        m_tooltip.object = image.get();
                    }
                }
            }

            for (auto &text : m_texts) {
                if (text->isActive()) text->update(deltaTime);
            }

            if (m_numOfMissionAvailable != 0) {
                handleMissions();
           }
           else {
                if (!m_completed && (m_currentMission == nullptr ||
                                     m_currentMission->isCompleted()))
                {
                    m_completed = true;
                    onComplete();
                }
            }
        }

        for (auto &button : m_buttons) {
            if (button->isActive() ) {
                button->update(deltaTime);
            }
        }

        handleTooltips(*previousTooltipObject);

        if (!m_isActive) unloadAll();
    }

    void Level::drawAll() {
        for (auto &object : m_objects ) {
            if (object->isSpawned() &&
                object->isCollidingWith(m_circle->getCollider()))
            {
                object->draw(-m_playerhalfSize);
            }

        }

        for (auto &enemy : m_enemies) {
            if (enemy->isSpawned() &&
                enemy->isCollidingWith(m_circle->getCollider()))
            {
                enemy->draw(-m_playerhalfSize);
            }
        }

        for (auto &wall : m_walls ) {
            if (wall->isSpawned() &&
                wall->isCollidingWith(m_circle->getCollider()))
            {
                wall->draw(*m_wallTexture, -m_playerhalfSize);
            }
        }

        if (m_player.isSpawned()) {
            m_player.draw(-m_playerhalfSize);
        }

        if (m_circle->isSpawned()) {
            m_circle->draw();
        }

        // Draw UI elements on top
        if (m_playerLivesIcon->isSpawned()) {
            m_playerLivesIcon->draw();
        }

        for (auto &image : m_images) {
            if (image->isSpawned()) {
                image->draw();
            }
        }

        for (auto &button : m_buttons) {
            if (button->isSpawned()) {
                button->draw();
            }
        }

        for (auto &text : m_texts) {
            if (text->isSpawned()) {
                text->draw();
            }
        }

        if (m_tooltip.tooltipImage != nullptr && m_tooltip.draw) {
            if (m_tooltip.tooltipImage->isSpawned()) {
                m_tooltip.tooltipImage->draw();
            }
        }

        if (m_missionCompleteImage->isActive() &&
            m_missionCompleteImage->isSpawned())
        {
            m_missionCompleteImage->draw();
        }
    }

    void Level::createBoundry() {
        int numOfColumns = (m_levelSize.w / m_wallSize.w) +
                        static_cast<int>(static_cast<bool>(m_levelSize.w %
                                                           m_wallSize.w));
        int leftPosition = static_cast<int>(-(numOfColumns / 2.0f) *
                                            m_wallSize.w);
        int rightPosition = -leftPosition - m_wallSize.w;

        int numOfRows = (m_levelSize.h / m_wallSize.h) +
                        static_cast<int>(static_cast<bool>(m_levelSize.h %
                                                           m_wallSize.h));
        int topPosition = static_cast<int>(-(numOfRows / 2.0f) * m_wallSize.h);
        int bottomPosition = -topPosition - m_wallSize.h;
       
        int longerSideNumOfWalls = numOfColumns > numOfRows ?
                                   numOfColumns : numOfRows;
        
        bool lastOnUnevenColumns = false;
        bool lastOnUnevenRows = false;
        for (int pos = 0; pos < longerSideNumOfWalls &&
                          longerSideNumOfWalls > 0; ++pos)
        {
            int halfColumns = numOfColumns & 1 ?
                             (numOfColumns / 2) + 1 : numOfColumns / 2;

            int halfRows = numOfRows & 1 ? (numOfRows / 2) + 1 : numOfRows / 2;

            if (pos < halfColumns) {
                // top left half
                m_walls.emplace_back(std::move(
                                      std::make_unique<TiledWall>(
                                                m_camera,
                                                Vector2d<int>{leftPosition +
                                                               (pos *
                                                                m_wallSize.w),
                                                              topPosition},
                                                m_wallSize)
                                    )
                );
                // bottom left half
                m_walls.emplace_back(std::move(
                                      std::make_unique<TiledWall>(
                                                m_camera,
                                                Vector2d<int>(leftPosition +
                                                               (pos *
                                                                m_wallSize.w),
                                                              bottomPosition),
                                                m_wallSize)
                                    )
                );
                
                lastOnUnevenColumns = numOfColumns & 1 && pos == halfColumns;
                if (!lastOnUnevenColumns) {
                    // top right half
                    m_walls.emplace_back(std::move(
                                         std::make_unique<TiledWall>(
                                                m_camera,
                                                Vector2d<int>{rightPosition -
                                                               (pos *
                                                                m_wallSize.w),
                                                              topPosition},
                                                m_wallSize)
                                        )
                    );                              
                    // bottom right half
                    m_walls.emplace_back(std::move(
                                          std::make_unique<TiledWall>(
                                                m_camera,
                                                Vector2d<int>{rightPosition -
                                                               (pos *
                                                                m_wallSize.w),
                                                              bottomPosition},
                                                m_wallSize)
                                        )
                    );
                }
            }
            
            if (pos > 0 && pos < numOfRows) {
                // left top half
                m_walls.emplace_back(std::move(
                                      std::make_unique<TiledWall>(
                                                m_camera,
                                                Vector2d<int>{leftPosition,
                                                              topPosition +
                                                               (pos *
                                                                m_wallSize.h)},
                                                m_wallSize)
                                    )
                );
                // right top half
                m_walls.emplace_back(std::move(
                                      std::make_unique<TiledWall>(
                                              m_camera,
                                              Vector2d<int>{rightPosition,
                                                             topPosition +
                                                               (pos *
                                                                m_wallSize.h)},
                                              m_wallSize)
                                    )
                );
                                                                
                lastOnUnevenRows = numOfRows & 1 && pos == halfRows;
                if (!lastOnUnevenRows) {
                    // left bottom half
                    m_walls.emplace_back(std::move(
                                          std::make_unique<TiledWall>(
                                                m_camera,
                                                Vector2d<int>{leftPosition,
                                                              bottomPosition -
                                                               (pos *
                                                                m_wallSize.h)},
                                                m_wallSize)
                                        )
                    );
                    // right bottom half    
                    m_walls.emplace_back(std::move(
                                          std::make_unique<TiledWall>(
                                                m_camera,
                                                Vector2d<int>{rightPosition,
                                                              bottomPosition -
                                                               (pos *
                                                                m_wallSize.h)},
                                                m_wallSize)
                                        )
                    );
                }
            }
        }
    }

    void Level::handleTooltips(const DrawableObject &previousTooltipObject) {
        if (&previousTooltipObject != m_tooltip.object && m_tooltip.object != nullptr)
        {
            auto text =  m_tooltip.object->getTooltipInfo();
            if (!text.empty()) {
                m_tooltip.tooltipImage = std::move(
                                          std::make_unique<Text>(
                                                    m_camera,
                                                    text,
                                                    Vector2d<int>{-INT_MAX,
                                                                  -INT_MAX},
                                                    AlignSide::Left, 8,
                                                    DescriptionFont,
                                                    BackgroundColour,
                                                    ForegroundColour)
                );
                m_tooltip.tooltipImage->spawn();
                m_tooltip.tooltipImage->start();
            }
            else {
                m_tooltip.tooltipImage.reset();
            }
        }
        else if (&previousTooltipObject == m_tooltip.object &&
                  m_tooltip.object != nullptr)
        {
            if (m_tooltip.tooltipImage != nullptr) {
                setTooltipPosition();
            }
        }
    }

    void Level::setTooltipPosition() {
        auto drawScale = m_camera.getDrawScale();

        auto windowSize = m_camera.getWindowSize();
        auto screenSizeInWindow = GameConstants::GameScreenSize * drawScale;
        auto screenMatteSize = (windowSize - screenSizeInWindow) / 2;

        Vector2d<int> mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        int tooltipOffset = 7;
        auto tooltipPosition = static_cast<Vector2d<float>>(mousePosition -
                                                            screenMatteSize) /
                               screenSizeInWindow *
                               GameConstants::GameScreenSize +
                               tooltipOffset;

        m_tooltip.tooltipImage->setPosition(tooltipPosition);
        m_tooltip.draw = true;
    }

    void Level::handleMissions() {
        bool missionCompleted = m_currentMission != nullptr &&
                                m_currentMission->isCompleted() &&
                               !m_missionChangeDelayStarted;

        if (missionCompleted) {
            m_currentMission->onComplete();
            m_missionCompleteSound.play();
        }

        bool shouldFindNewMission = m_numOfMissionAvailable != 0 &&
                                   (m_currentMission == nullptr ||
                                   (m_currentMission != nullptr &&
                                    m_currentMission->isCompleted()));

        if (shouldFindNewMission) {
            // skip delay on start
            if (!m_missionChangeDelayStarted && m_currentMission != nullptr) {
                delayNewMission();
            }

            bool missionAndDelayFinished =
                                       (m_missionChangeDelay.finished() &&
                                        m_missionChangeDelayStarted == true) ||
                                        m_currentMission == nullptr;

            if (missionAndDelayFinished) {
                findNewMission();
            }
        }

        if (m_currentMission != nullptr && !m_currentMission->isCompleted()) {
            m_currentMission->checkIfCompleted();
        } 
    }
    
    void Level::findNewMission() {
        m_missionCompleteImage->deactivate();
        m_numOfMissionAvailable = 0;
        for (auto &mission : m_missions) {
            if (!mission->isCompleted()) {
                ++m_numOfMissionAvailable;
                m_currentMission = mission.get();
                
                m_currentMissionTitle->spawn();
                m_currentMissionTitle->start();
                auto title = m_currentMission->getTitle();
                m_currentMissionTitle->changeText(title);

                m_currentMissionDescripion->spawn();
                m_currentMissionDescripion->start();
                auto description = m_currentMission->getDescription();
                m_currentMissionDescripion->changeText(description);

                break;
            } 
        }
        if (m_numOfMissionAvailable == 0) {
            m_currentMissionTitle->despawn();
            m_currentMissionDescripion->despawn();
        }

        m_missionChangeDelayStarted = false;
    }

    void Level::delayNewMission() {
        m_missionChangeDelay.reset();
        m_missionChangeDelayStarted = true;

        m_currentMissionTitle->despawn();
        m_currentMissionDescripion->despawn();

        m_missionCompleteImage->activate();
    }

    void Level::handleCollisions() {
        handleObjectsCollisions();
        handleEnemiesCollisions();
        handleWallsCollisions();
    }

    void Level::handleObjectsCollisions() {
        for (auto object = m_objects.begin();
             object != m_objects.end();
             ++object)
        {
            if (m_player.isCollidable() && (*object)->isCollidable() &&
                m_player.isActive() && (*object)->isActive() &&
                (*object)->isCollidingWith(m_circle->getCollider()))
            {
                m_player.handleCollision(*(*object));
                (*object)->handleCollision(m_player);
            }
            
            for (auto enemy = m_enemies.begin();
                 enemy != m_enemies.end();
                 ++enemy)
            {
                if ((*enemy)->isCollidable() && (*object)->isCollidable() &&
                    (*enemy)->isActive() && (*object)->isActive() &&
                    (*enemy)->isCollidingWith(m_circle->getCollider()) &&
                    (*object)->isCollidingWith(m_circle->getCollider()) &&
                    (*object)->getType() != ObjectType::Projectile)
                {
                    (*enemy)->handleCollision(*(*object));
                    (*object)->handleCollision(*(*enemy));
                }
            }
            
            for (auto wall = m_walls.begin();
                 wall != m_walls.end();
                 ++wall)
            {
                if ((*wall)->isCollidable() && (*object)->isCollidable() &&
                    (*wall)->isActive() && (*object)->isActive() &&
                    (*wall)->isCollidingWith(m_circle->getCollider()) &&
                    (*object)->isCollidingWith(m_circle->getCollider()))
                {
                    (*object)->handleCollision(*(*wall));
                    (*wall)->handleCollision(*(*object));
                }
            }
        }
    }
    void Level::handleEnemiesCollisions() {
        for (auto enemy = m_enemies.begin();
            enemy != m_enemies.end();
            ++enemy)
        {
            if (m_player.isCollidable() && (*enemy)->isCollidable() &&
                m_player.isActive() && (*enemy)->isActive() &&
                (*enemy)->isCollidingWith(m_circle->getCollider()))
            {
                m_player.handleCollision(*(*enemy));
                (*enemy)->handleCollision(m_player);
            }
            
            for (auto enemy2 = enemy + 1;
                enemy2 != m_enemies.end() && m_enemies.size() > 1;
                ++enemy2)
            {
                if ((*enemy2)->isCollidable() && (*enemy)->isCollidable() &&
                    (*enemy2)->isActive() && (*enemy)->isActive() &&
                    (*enemy2)->isCollidingWith(m_circle->getCollider()) &&
                    (*enemy)->isCollidingWith(m_circle->getCollider()))
                {
                    (*enemy2)->handleCollision(*(*enemy));
                    (*enemy)->handleCollision(*(*enemy2));
                }
            }

            for (auto wall = m_walls.begin();
                wall != m_walls.end();
                ++wall)
            {
                if ((*wall)->isCollidable() && (*enemy)->isCollidable() &&
                    (*wall)->isActive() && (*enemy)->isActive() &&
                    (*wall)->isCollidingWith(m_circle->getCollider()) &&
                    (*enemy)->isCollidingWith(m_circle->getCollider()))
                {
                    (*enemy)->handleCollision(*(*wall));
                    (*wall)->handleCollision(*(*enemy));
                }
            }
        }
    }
    void Level::handleWallsCollisions() {
        for (auto wall = m_walls.begin();
            wall != m_walls.end();
            ++wall)
        {
            if (m_player.isCollidable() && (*wall)->isCollidable() &&
                m_player.isActive() && (*wall)->isActive() &&
                (*wall)->isCollidingWith(m_circle->getCollider()))
            {
                m_player.handleCollision(*(*wall));
                (*wall)->handleCollision(m_player);
            }
        }
    }


    void Level::handleTimeOfDay(float deltaTime) {
        if (!m_paused) {
            auto previousTimeOfDay = m_timeOfDay;

            m_time += deltaTime / m_secondsPerHour;
            if (m_time> HoursPerDay) {
                m_time = 0;
            }

            if (m_time > m_dayDuration.first &&
                m_time < m_dayDuration.second)
            {
                m_timeOfDay = TimeOfDay::Day;
            }
            else if (m_time > m_nightDuration.first ||
                     m_time < m_nightDuration.second)
            {
                m_timeOfDay = TimeOfDay::Night;
            }
            else {
                m_timeOfDay = TimeOfDay::SunsetOrDawn;
            }

            if (m_timeOfDay != previousTimeOfDay &&
                m_timeOfDayIcon != nullptr)
            {
                m_timeOfDayIcon->changeTimeOfDay(m_timeOfDay);
                switch (m_timeOfDay)
                {
                case TimeOfDay::Day:
                    std::for_each(m_enemies.begin(), m_enemies.end(),
                                    [&](auto &enemy) {
                                        if (enemy->isActive()) {
                                            enemy->onDay(deltaTime);
                                        }
                                    });
                    m_timeOfDayIcon->setTooltipInfo(DaytimeTooltipInfo);
                    break;

                case TimeOfDay::SunsetOrDawn:
                    std::for_each(m_enemies.begin(), m_enemies.end(),
                                    [&](auto &enemy){
                                        if (enemy->isActive()) {
                                            enemy->onSunsetOrDawn(deltaTime);
                                        }
                                    });
                    m_timeOfDayIcon->setTooltipInfo(SunsetDawnTooltipInfo);
                    break;

                case TimeOfDay::Night:
                    std::for_each(m_enemies.begin(), m_enemies.end(),
                                    [&](auto &enemy){
                                        if (enemy->isActive()) {
                                            enemy->onNight(deltaTime);
                                        }
                                    });
                    m_timeOfDayIcon->setTooltipInfo(NighttimeTooltipInfo);
                    break;
                }
            }

            float circleAngle = ((m_time / HoursPerDay) * 360) + 180;
            if (circleAngle> 360) {
                circleAngle -= 360;
            }
            m_circle->setAngle(circleAngle);
        }
    }

    void Level::handleInput(float deltaTime) {
        auto keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_ESCAPE] &&
            m_pauseDelay.finished() && m_pausable)
        {
            handlePausing();
            m_pauseDelay.reset();
        }

        onInput(deltaTime);
    }

    void Level::createPauseMenu() {
        if (m_pausable) {
            m_texts.emplace_back(std::move(
                                  std::make_unique<Text>(
                                                m_camera, "| Paused |",
                                                Vector2d<int>{-INT_MAX,
                                                              -INT_MAX},
                                                AlignSide::VerticalCentre |
                                                 AlignSide::HorizontalCentre,
                                                14, DefaultFont,
                                                ForegroundColour,
                                                BackgroundColour)
                                )
            );
            m_pauseMenu.title = m_texts.back().get();

            m_buttons.emplace_back(std::move(
                                    std::make_unique<Button>(
                                                PauseBtnTexturePath,
                                                m_camera, "Pause",
                                                Vector2d<int>{0, 0})
                                   )
            );
            m_pauseMenu.pause = m_buttons.back().get();
            m_pauseMenu.pause->connectOnClick(std::bind(&Level::handlePausing,
                                                         this));

            m_buttons.emplace_back(std::move(
                                    std::make_unique<Button>(
                                                ResumeBtnTexturePath,
                                                m_camera, "Resume",
                                                Vector2d<int>{-INT_MAX,
                                                              -INT_MAX})
                                   )
            );
            m_pauseMenu.resume = m_buttons.back().get();
            m_pauseMenu.resume->connectOnClick(std::bind(&Level::closePauseMenu,
                                                          this));
            
            m_buttons.emplace_back(std::move(
                                    std::make_unique<Button>(
                                                ExitBtnTexturePath,
                                                m_camera, "Exit",
                                                Vector2d<int>{-INT_MAX,
                                                              -INT_MAX})
                                   )
            );
            m_pauseMenu.exit = m_buttons.back().get();
            m_pauseMenu.exit->connectOnClick(std::bind(&Level::quitToMenu,
                                                        this));
        }
    }

    void Level::openPauseMenu() {
        m_paused = true;

        m_pauseMenu.title->setPosition(static_cast<float>(UICentrePosition.x),
                                       static_cast<float>(UICentrePosition.y -
                                                        70)
        );

        m_pauseMenu.resume->setPosition(static_cast<float>(UICentrePosition.x -
                                                         55),
                                        static_cast<float>(UICentrePosition.y -
                                                         50)
        );

        m_pauseMenu.exit->setPosition(static_cast<float>(UICentrePosition.x -
                                                       55),
                                      static_cast<float>(UICentrePosition.y -
                                                       10)
        );
    }

    void Level::closePauseMenu() {
        m_paused = false;
        m_pauseMenu.title->setPosition(static_cast<float>(-INT_MAX),
                                       static_cast<float>(-INT_MAX)
        );
        m_pauseMenu.resume->setPosition(static_cast<float>(-INT_MAX),
                                        static_cast<float>(-INT_MAX)
        );
        m_pauseMenu.exit->setPosition(static_cast<float>(-INT_MAX),
                                      static_cast<float>(-INT_MAX)
        );
    }

    void Level::handlePausing() {
        if (m_pausable) {
            if (m_paused) {
                closePauseMenu();
            }
            else {openPauseMenu();
            }
        }
    }

    void Level::createGameOverScreen() {
        m_texts.emplace_back(std::move(
                              std::make_unique<Text>(
                                            m_camera, "| YOU DIED! |",
                                            Vector2d<int>{-INT_MAX, -INT_MAX},
                                            AlignSide::VerticalCentre |
                                             AlignSide::HorizontalCentre,
                                            20,
                                            GameConstants::DefaultFont,
                                            GameConstants::DarkRedColour,
                                            GameConstants::BackgroundColour)
                            )
        );
        m_gameOverScreen.title = m_texts.back().get();

        m_texts.emplace_back(std::move(
                              std::make_unique<Text>(
                                            m_camera, "",
                                            Vector2d<int>{-INT_MAX, -INT_MAX},
                                            AlignSide::Up |
                                             AlignSide::HorizontalCentre,
                                            14,
                                            GameConstants::DescriptionFont,
                                            GameConstants::ForegroundColour,
                                            GameConstants::BackgroundColour)
                            )
        );
        m_gameOverScreen.description = m_texts.back().get();

        m_gameOverScreen.exit = m_pauseMenu.exit;
    }

    void Level::openGameOverScreen() {
        m_pausable = false;

        Vector2d<int> pos{GameConstants::UICentrePosition.x,
                          GameConstants::UICentrePosition.y - 67};
        m_gameOverScreen.title->setPosition(pos);
        
        std::string description = "You were slain by the " +
                                   m_player.getKillersName() +
                                   ".\n First you lost your arms,"
                                   " then your legs.\n"
                                   "You tried bleeding on him to death\n"
                                   "but it didn't work.\n"
                                   "In the end you called it a draw.";
        m_gameOverScreen.description->changeText(description);

        pos = {GameConstants::UICentrePosition.x,
               GameConstants::UICentrePosition.y - 50};
        m_gameOverScreen.description->setPosition(pos);

        pos = {GameConstants::UICentrePosition.x - 55,
               GameConstants::UICentrePosition.y + 24};
        m_gameOverScreen.exit->setPosition(pos);
    }

    void Level::quitToMenu() {
        m_game.changeLevel(LevelList::MainMenu);
    }

    void Level::load() {
        spawn();
        start();
    }

    void Level::unload() {
        m_isActive = false;
        m_completed = false;
        m_numOfMissionAvailable = UINT8_MAX;
    }
    
    void Level::unloadAll() {
        m_circle->despawn();
        m_playerLivesIcon->despawn();
        m_paused = false;
    
        m_wallTexture.reset();

        m_enemies.clear();
        m_objects.clear();
        m_walls.clear();
        m_images.clear();
        m_buttons.clear();
        m_texts.clear();
        m_missions.clear();

        m_timeOfDayIcon = nullptr;
        m_pauseMenu = {nullptr, nullptr, nullptr, nullptr};
        m_gameOverScreen = {nullptr, nullptr, nullptr};
        m_tooltip = {false, nullptr, nullptr},
        m_currentMission = nullptr;
        m_currentMissionTitle = nullptr;
        m_currentMissionDescripion = nullptr;
        
        onUnload();
        despawn();
    }

    void Level::calculateGridPositions() {
        int rows = m_levelSize.h / m_wallSize.h;
        int columns = m_levelSize.w / m_wallSize.w;

        int rowsOffset = static_cast<int>(static_cast<bool>((m_levelSize.h /
                                                             m_wallSize.h) &
                                                            1)) *
                         (m_wallSize.w / 2);
        for (int i = 0; i < rows-1; ++i) {
            m_rowPositions.emplace_back(((i - (rows-2)/2) * m_wallSize.h) -
                                        rowsOffset);
        }

        int columnsOffset = static_cast<int>(static_cast<bool>((m_levelSize.w /
                                                             m_wallSize.w) &
                                                            1)) *
                         (m_wallSize.h / 2);
        for (int i = -(columns-2)/2; i <= (columns-2)/2; ++i) {
            m_columnPositions.emplace_back((i * m_wallSize.w) - columnsOffset);
        }
    }

    std::vector<Actor *> Level::getObjectsInsideCircle() {
        std::vector<Actor *> objectsInside;
        objectsInside.emplace_back(&m_player);

        for (auto &wall : m_walls) {
            if (wall->isActive() &&
                wall->isCollidingWith(m_circle->getCollider()))
            {
                objectsInside.emplace_back(wall.get());
            }
        }

        for (auto &obj : m_objects) {
            if (obj->isActive() &&
                obj->isCollidingWith(m_circle->getCollider()))
            {
                objectsInside.emplace_back(obj.get());
            }
        }

        for (auto &enemy : m_enemies) {
            if (enemy->isActive() &&
                enemy->isCollidingWith(m_circle->getCollider()))
            {
                objectsInside.emplace_back(enemy.get());
            }
        }
        return objectsInside;
    }
    
} // namespace house