#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <stdint.h>
#include "SDL.h"

#include "Vector2d.h"
namespace house {

    namespace GameConstants {

        constexpr Vector2d<int> GameScreenSize {384, 216};
        constexpr float GameScreenRatio {static_cast<float>(GameScreenSize.x) /
                                         GameScreenSize.y};
        
        constexpr const char *DefaultFont = "fonts/KaushanScript-Regular.otf";
        constexpr const char *DescriptionFont = "fonts/slkscr.ttf";
        constexpr uint8_t DefaultFontSize = 16;

        constexpr Vector2d<int> UICentrePosition {192, 108};
        constexpr Vector2d<int> CentrePosition   {  0,   0};

        constexpr Vector2d<int> CircleSize       {166, 166};

        constexpr SDL_Color BackgroundMask       {255,   0, 200, 255};
        constexpr SDL_Color BackgroundColour     {160, 140, 110, 255};
        constexpr SDL_Color ForegroundColour     {  0,  15,   0, 255};
        constexpr SDL_Color DarkRedColour        { 15,   0,   0, 255};
        constexpr SDL_Color TransparentColour    {  0,   0,   0,   0};

    } // namespace GameConstants

} // namespace house

#endif // !GAME_CONSTANTS_H