#ifndef PLAYER_LIVES_ICON_H
#define PLAYER_LIVES_ICON_H

#include "Image.h"

namespace house {

    class PlayerLivesIcon : public Image {
        private:
         static constexpr const char *TexturePath = "gfx\\ui\\lives.png";
         static constexpr const char *Name        = "Player lives icon";
         
         int SpriteWidth;

         Vector2d<int> ScreenPosition;

         void onSpawn();

        public:
         PlayerLivesIcon(Camera &camera, const std::string &tooltipInfo = "");

         void onStart();
         void onUpdate(float deltaTime);

         void setLives(int lives);
    };

} // namespace house

#endif // PLAYER_LIVES_ICON_H