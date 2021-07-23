#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Camera.h"

#include "Vector2d.h"
#include "SDLSmartPtrs.h"

#include "gameConstants.h"

#include "GameException.h"

namespace house {

    class TextureManager {
        public:
         [[nodiscard]] static SDL_Texture* loadTexture(SDL_Renderer *renderer,
                                               const std::string &texturePath);

         [[nodiscard]] static SDL_Texture* loadText(
               SDL_Renderer *renderer,
               const std::string &text,
               const std::string& fontPath = GameConstants::DefaultFont,
               int fontSize                = GameConstants::DefaultFontSize,
               SDL_Colour fontColour       = GameConstants::ForegroundColour,
               SDL_Colour backgroundColour = GameConstants::TransparentColour);

         static void changeColour(SDL_Surface *surface,
                                  SDL_Colour colourToChange,
                                  SDL_Colour newColour);

    };
    
    bool operator==(const SDL_Color &lhs, const SDL_Color &rhs);

} // namespace house

#endif // !TEXTURE_MANAGER_H