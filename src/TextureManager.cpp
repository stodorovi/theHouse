#include "TextureManager.h"

namespace house {

    [[nodiscard]] SDL_Texture* TextureManager::loadTexture(
                                                SDL_Renderer *renderer,
                                                const std::string &texturePath)
    {
        SDL_Surface *surface = IMG_Load(texturePath.c_str());
        if (!texturePath.empty() && surface == nullptr) {
            auto errorMsg = IMG_GetError();
            throw GameException(errorMsg);
       }

        SDL_Surface *formatedSurface = nullptr;

        Uint32 surfaceFormat = surface->format->format;
        Uint32 targetFormat = SDL_PIXELFORMAT_RGBA32;
        if (surfaceFormat != targetFormat) {
            formatedSurface = SDL_ConvertSurfaceFormat(surface,
                                                       targetFormat, 0);
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
        
        if (!texturePath.empty()) {
            if (surface) {
                changeColour(surface, GameConstants::BackgroundMask,
                                      GameConstants::BackgroundColour);
            }
            else if (formatedSurface) {
                changeColour(formatedSurface,
                             GameConstants::BackgroundMask,
                             GameConstants::BackgroundColour);
            }
        }

        SDL_Texture *outTexture = nullptr;
        if (surface) {
            outTexture = SDL_CreateTextureFromSurface(renderer, surface);
        }
        else if (formatedSurface) {
            outTexture = SDL_CreateTextureFromSurface(renderer,
                                                      formatedSurface);
        }

        if (surface) {
            SDL_FreeSurface(surface);
        }
        else if (formatedSurface) {
            SDL_FreeSurface(formatedSurface);
        }

        return outTexture;
    }

    [[nodiscard]] SDL_Texture* TextureManager::loadText(
                                                SDL_Renderer *renderer,
                                                const std::string &text,
                                                const std::string& fontPath,
                                                int fontSize,
                                                SDL_Colour fontColour,
                                                SDL_Colour backgroundColour)
    {
        TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (font == nullptr) {
            const char *ttfMsg = TTF_GetError();
            throw GameException(ttfMsg);
        }
        
        std::stringstream textS(text);
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(textS, line, '\n')) {
            lines.emplace_back(line);
        }

        int finalSurfaceWidth = 0;
        int finalSurfaceHeight = 0;
        SDL_Surface * surface;
        std::vector<SDL_Surface*> textSurfaces;
        for (auto &line : lines) {
            if (line.length() != 0) {
                surface = TTF_RenderUTF8_Solid(font, line.c_str(), fontColour);
                if (surface->w > finalSurfaceWidth) {
                    finalSurfaceWidth = surface->w;
                }
                finalSurfaceHeight += surface->h;
                textSurfaces.emplace_back(surface);
            }
        }
        // padding
        finalSurfaceWidth += 10;
        finalSurfaceHeight += 4;

        SDL_Surface *finalSurface = SDL_CreateRGBSurface(
                                                    0,
                                                    finalSurfaceWidth,
                                                    finalSurfaceHeight,
                                                    32,
                                                    0xff000000, 0x000ff0000,
                                                    0x0000ff00, 0x000000ff);

        SDL_FillRect(finalSurface, NULL, SDL_MapRGBA(finalSurface->format,
                                                     backgroundColour.r,
                                                     backgroundColour.g,
                                                     backgroundColour.b,
                                                     backgroundColour.a));

        SDL_Rect destRect {5, 2, 0, 0};
        for (auto surface : textSurfaces) {
            destRect.w = surface->w;
            destRect.h = surface->h;
            SDL_BlitSurface(surface, NULL, finalSurface, &destRect);
            destRect.y += surface->h;

            SDL_FreeSurface(surface);
        }
        
        SDL_Texture *outTexture = SDL_CreateTextureFromSurface(renderer,
                                                               finalSurface);
        SDL_FreeSurface(finalSurface);

        return outTexture;
    }

    void TextureManager::changeColour(SDL_Surface *surface,
                                      SDL_Colour colourToChange,
                                      SDL_Colour newColour)
    {
        SDL_LockSurface(surface);

        int numOfPixels = surface->w * surface->h;

        uint32_t *pixelData = (uint32_t *) surface->pixels;

        for (size_t pixelNum = 0; pixelNum < numOfPixels; ++pixelNum) {
            SDL_Colour *pixelColour = (SDL_Color *) &pixelData[pixelNum];

            if (pixelColour != nullptr &&
               *pixelColour == GameConstants::BackgroundMask)
            {
                pixelData[pixelNum] = *(uint32_t *) &newColour;
            }
        }

        SDL_UnlockSurface(surface);
    }

    bool operator== (const SDL_Color &lhs, const SDL_Color &rhs) {
        return {lhs.r == rhs.r &&
                lhs.g == rhs.g &&
                lhs.b == rhs.b &&
                rhs.a == rhs.a};
    }
    
} // namespace house