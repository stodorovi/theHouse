#include "Key.h"

namespace house {
    
    Key::Key(Camera &camera, Vector2d<int> startingPosition)
    : Actor(TexturePath, camera, Name, startingPosition),
    m_pickedUpSound{AudioManager::loadAudioWav(PickedUpSoundPath)}
    {}

    void Key::onSpawn() {
        
    }

    void Key::onStart() {

    }

    
    void Key::onUpdate(float deltaTime) {
        
    }

    void Key::onCollision(const Actor &other) {
        if (other.getType() == ObjectType::Player) {
            m_pickedUpSound.play();
            despawn();
        }
    }

} // namespace house