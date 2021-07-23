#include "Door.h"

namespace house {

    Door::Door(Camera &camera, Vector2d<int> startingPosition,
               Orientation orientation)
    : Actor(TexturePath, camera, Name, startingPosition),
    m_orientation{orientation},
    m_destroyedSound{AudioManager::loadAudioWav(DestroyedSoundPath)}
    {}

    void Door::onSpawn() {
        if (m_orientation == Orientation::Horizontal) {
            m_srcDrawRect = m_horizontalSrcRect;
            m_size.h /= 2;
            m_screenSize.h /= 2;
        }
        else {
            m_srcDrawRect = m_vertialSrcRect;
        }
        m_size.w /= 3;
        m_screenSize.w /= 3;
    }

    void Door::onStart() {

    }

    
    void Door::onUpdate(float deltaTime) {
        
    }

    void Door::onCollision(const Actor &other) {
        bool projectile = other.getType() == ObjectType::Projectile;

        bool characterAttacking = false;
        bool characterFacingDoor = false;
        auto objType = other.getType();
        if (objType == ObjectType::Enemy || objType == ObjectType::Player) {
            auto &character = dynamic_cast<const Character&>(other);
            auto charPos = character.getPosition();
            auto facingDirection = character.getFacingDirection();

            characterAttacking = character.getCurrentAction() ==
                                 Action::Attacking;

            characterFacingDoor = (charPos.x < m_position.x) &&
                                   facingDirection == Direction::Right ||
                                  (charPos.x > m_position.x) &&
                                   facingDirection == Direction::Left ||
                                  (charPos.y < m_position.y) &&
                                   facingDirection == Direction::Down ||
                                  (charPos.y > m_position.y) &&
                                   facingDirection == Direction::Up;
        }

        if (projectile || (characterAttacking && characterFacingDoor)) {
            breakDoor();
        }
    }

    void Door::breakDoor() {
        if (m_orientation == Orientation::Horizontal) {
           m_srcDrawRect.y = m_horizontalSrcRect.h; 
        }
        else {
            m_srcDrawRect.x = m_vertialSrcRect.h;
        }

        m_destroyedSound.play();
        deactivate();
    }

} // namespace house