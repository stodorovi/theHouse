#include "Text.h"

namespace house {
    Text::Text(Camera &camera, const std::string &text,
               Vector2d<int> startingPosition, AlignSide alignFlags,
               int fontSize, const std::string& fontPath,
               SDL_Colour fontColour, SDL_Colour backgroundColour)
    : DrawableObject("", camera, text, startingPosition),
    m_fontPath{fontPath}, m_fontSize{fontSize}, m_fontColour{fontColour},
    m_backgroundColour{backgroundColour}, m_alignSide{alignFlags}
    {}

    void Text::spawn() {
        auto *renderer = &m_camera.getRenderer();
        m_texture.reset(TextureManager::loadText(renderer, m_name, m_fontPath,
                                                 m_fontSize, m_fontColour,
                                                 m_backgroundColour));
            
        auto format = m_camera.getWindowPixelFormat();
        SDL_QueryTexture(m_texture.get(), &format, NULL,
                        &m_size.w, &m_size.h);
        m_srcDrawRect = {0, 0, m_size.w, m_size.h};

        m_screenSize = m_size * m_camera.getDrawScale();

        m_spawned = true;
        onSpawn();

        activate();
    }
    void Text::onSpawn() {
        
    }

    void Text::onStart() {

    }

    void Text::onUpdate(float deltaTime) {

    }

    void Text::changeText(const std::string &newText) {
        if (m_isActive) {
            m_name = newText;
            m_texture.reset(TextureManager::loadText(&m_camera.getRenderer(),
                                                      m_name, m_fontPath,
                                                      m_fontSize, m_fontColour,
                                                      m_backgroundColour));
            
            auto format = m_camera.getWindowPixelFormat();
            SDL_QueryTexture(m_texture.get(), &format, NULL,
                            &m_size.w, &m_size.h);

            m_srcDrawRect = {0, 0, m_size.w, m_size.h};

            m_screenSize = m_size * m_camera.getDrawScale();
        }
    }

    void Text::draw(Vector2d<int> offset) {
        Vector2d<int> align;
        auto alignFlags = m_alignSide;

        if (static_cast<bool>(alignFlags & AlignSide::Up)) {
            align.y = 0;
        }
        if (static_cast<bool>(alignFlags & AlignSide::VerticalCentre)) {
            align.y = -m_screenSize.y / 2;
        }
        if (static_cast<bool>(alignFlags & AlignSide::Down)) {
            align.y = -m_screenSize.y;
        }

        if (static_cast<bool>(alignFlags & AlignSide::Left)) {
            align.x = 0;
        }
        if (static_cast<bool>(alignFlags & AlignSide::HorizontalCentre)) {
            align.x = -m_screenSize.x / 2;
        }
        if (static_cast<bool>(alignFlags & AlignSide::Right)) {
            align.x = -m_screenSize.x;
        }

        auto drawScale = m_camera.getDrawScale();
        auto windowSize = m_camera.getWindowSize();
        auto halfWindowSize = windowSize / 2;
        Vector2d<int> drawDestVector = halfWindowSize -
                                     ((GameConstants::UICentrePosition -
                                        m_position + offset) * drawScale) +
                                       align;
                                       
        m_destDrawRect = {drawDestVector.x, drawDestVector.y,
                          m_screenSize.w, m_screenSize.h};

        SDL_RenderCopy(&m_camera.getRenderer(), m_texture.get(),
                       &m_srcDrawRect, &m_destDrawRect);
    }
 
} // namespace house