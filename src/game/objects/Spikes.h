#ifndef SPIKES_H
#define SPIKES_H

#include "Actor.h"
#include "Timer.h"

namespace house {
    
    class Spikes : public Actor {
        private:
         static constexpr const char *TexturePath = "gfx\\objects\\spikes.png";

         static constexpr const char *Name        = "Spikes";
         static constexpr const char *TooltipInfo = "There are spikes.\n"
                                                    " They hurt when raised,"
                                                    " so be careful.";

         static constexpr const char *RaiseSoundPath
                                            = "sfx\\objects\\spikesRaise.wav";
         static constexpr const char *LowerSoundPath
                                            = "sfx\\objects\\spikesLower.wav";

         Mix_Chunk_unique_ptr m_raiseSound;
         Mix_Chunk_unique_ptr m_lowerSound;

         void onStart();
         void onSpawn();
         void onUpdate(float deltaTime);

         bool m_raised;
         static constexpr uint16_t RaiseFrequency = 1500;
         
         Timer m_raiseAndLowerTimer;

         void raise();
         void lower();
        
        public:
         Spikes(Camera &camera, Vector2d<int> startingPosition);

         void onCollision(const Actor &other);

         bool isRaised() const noexcept;
    };
    
} // namespace house

#endif // !SPIKES_H