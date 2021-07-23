#ifndef TEXT_H
#define TEXT_H

#include "DrawableObject.h"


namespace house {
    enum class AlignSide {
        Left             = 1,
        HorizontalCentre = 1 << 1,
        Right            = 1 << 2,
        Up               = 1 << 3,
        VerticalCentre   = 1 << 4,
        Down             = 1 << 5
    };

    constexpr AlignSide operator| (AlignSide lhs, AlignSide rhs) {
        int resultValue = static_cast<int>(lhs) | static_cast<int>(rhs);
        AlignSide result = static_cast<AlignSide>(resultValue);

        return result;
    }

    constexpr AlignSide operator& (AlignSide lhs, AlignSide rhs) {
        int resultValue = static_cast<int>(lhs) & static_cast<int>(rhs);
        AlignSide result = static_cast<AlignSide>(resultValue);

        return result;
    }

    class Text : public DrawableObject {
        private:
         std::string m_fontPath;
        
         int m_fontSize;
         SDL_Colour m_fontColour;
         SDL_Colour m_backgroundColour;

         AlignSide m_alignSide;

        public:
         Text(Camera &camera, const std::string &text = "Text",
              Vector2d<int> startingPosition = {0, 0},
              AlignSide alignFlags = AlignSide::VerticalCentre |
                                     AlignSide::HorizontalCentre,
              int fontSize                = GameConstants::DefaultFontSize,
              const std::string& fontPath = GameConstants::DefaultFont,
              SDL_Colour fontColour       = GameConstants::ForegroundColour,
              SDL_Colour backgroundColour = GameConstants::TransparentColour);

         Text(const Text &other) = default;

         void onStart();
         void onUpdate(float deltaTime);

         void changeText(const std::string &text);

         void draw(Vector2d<int> offset = {0, 0});

         void spawn();
         void onSpawn();
    };

} // namespace house

#endif // !TEXT_H