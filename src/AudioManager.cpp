#include "AudioManager.h"

namespace house {

    [[nodiscard]] Mix_Chunk* AudioManager::loadAudioWav(
                                                const std::string &audioPath)
    {
        Mix_Chunk *outAudio = Mix_LoadWAV(audioPath.c_str());

        if (outAudio == nullptr && !audioPath.empty()) {
            std::stringstream errorMsg;
            errorMsg << "Couldn't open " << audioPath << "\n";
            throw GameException(errorMsg.str());
        }

        return outAudio;
    }   

} // namespace house