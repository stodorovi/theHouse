#include "Spikes.h"

namespace house {
    
    Spikes::Spikes(Camera &camera, Vector2d<int> startingPosition)
    : Actor(TexturePath, camera, Name, startingPosition, true, TooltipInfo),
    m_raised{false}, m_raiseAndLowerTimer{RaiseFrequency},
    m_raiseSound{AudioManager::loadAudioWav(RaiseSoundPath)},
    m_lowerSound{AudioManager::loadAudioWav(LowerSoundPath)}
    {
        m_type = ObjectType::Spikes;
    }

    void Spikes::onSpawn() {
        m_size.w /= 2;
        m_screenSize.w /= 2;
        m_srcDrawRect.w = m_size.w;
    }

    void Spikes::onStart() {
        
    }

    void Spikes::onUpdate(float deltaTime) {
        if (m_raiseAndLowerTimer.finished()) {
            if (m_raised) {
                lower();
            }
            else {
                raise();
            }

            m_raiseAndLowerTimer.reset();
        }
    }

    void Spikes::onCollision(const Actor &other) {
        if (m_raised) {
            lower();
        }

        m_raised = true; // to still be checked until the end of the frame
        deactivate();
    }

    void Spikes::raise() {
        m_srcDrawRect.x = m_size.w;
        m_raised = true;
        m_collidable = true;
        m_raiseSound.play();
    }

    void Spikes::lower() {
        m_srcDrawRect.x = 0;
        m_raised = false;
        m_collidable = false;
        m_lowerSound.play();
    }

    bool Spikes::isRaised() const noexcept {
        return m_raised;
    }
    
} // namespace house