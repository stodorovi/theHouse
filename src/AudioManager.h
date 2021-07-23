#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <string>

#include "SDL_mixer.h"
#include "GameException.h"

namespace house {

    class AudioManager {
        public:
         [[nodiscard]] static Mix_Chunk* loadAudioWav(const std::string &audioPath);
    };
} // namespace house

#endif // !AUDIO_MANAGER_H