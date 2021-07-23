#include "PlayerLivesIcon.h"
#include "Character.h"

namespace house {
    
    PlayerLivesIcon::PlayerLivesIcon(Camera &camera,
                                     const std::string &tooltipInfo)
    : Image(TexturePath, camera, Name,
            GameConstants::UICentrePosition, 0.0, tooltipInfo),
    SpriteWidth {0}, ScreenPosition{0, 0}
    {}

    void PlayerLivesIcon::onSpawn() {
        m_position.x = GameConstants::UICentrePosition.x -
                        (GameConstants::CircleSize.x / 2) + 
                        m_size.x * (2.0f / 3) - (m_size.w / 3);

        m_position.y = GameConstants::UICentrePosition.y +
                        (GameConstants::CircleSize.y / 2) +
                        m_size.y * (2.0f / 3) - m_size.h;

        SpriteWidth = m_size.w; 
        ScreenPosition = m_position;
    }

    void PlayerLivesIcon::onStart() {
        
    }

    void PlayerLivesIcon::onUpdate(float deltaTime) {

    }

    void PlayerLivesIcon::setLives(int lives) {
        if (lives > Character::DefaultNumberOfLives) {
            lives = Character::DefaultNumberOfLives;
        }
        else  if (lives < 0) {
            lives = 0;
        }

        float livesRatio = lives /
                           static_cast<float>(Character::DefaultNumberOfLives);

        m_size.w         = static_cast<int>(livesRatio * SpriteWidth);
        m_screenSize.w   = static_cast<int>(livesRatio * SpriteWidth *
                                           m_camera.getDrawScale());
        m_srcDrawRect.x  = SpriteWidth - m_size.w;
        

        float offset = (livesRatio == 1) ?
                        0 : (SpriteWidth / 2.0f - m_size.w / 2.0f);
        m_position.x = ScreenPosition.x + offset;
    }

} // namespace house