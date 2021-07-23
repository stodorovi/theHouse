#include "Camera.h"

namespace house {

    Camera::Camera(SDL_Window &window, const SDL_Color &backgroundColor,
                   const std::string &name)
    :GameObject(name, Vector2d<int>{0, 0}),
    m_renderer {nullptr}, m_backgroundColor {backgroundColor},
    m_windowPixelFormat {0}, m_windowSize {0, 0}, m_drawScale{0.0f}
    {
        m_renderer.reset(SDL_CreateRenderer(&window, -1, 0));
        if (m_renderer == nullptr) {
            throw GameException(SDL_GetError());
        }

        m_windowPixelFormat = SDL_GetWindowPixelFormat(&window);
        SDL_GetWindowSize(&window, &m_windowSize.w, &m_windowSize.h);

        Vector2d<float> drawScaleVector {
                            static_cast<Vector2d<float>>(m_windowSize) /
                            GameConstants::GameScreenSize
                        };

        m_drawScale = (drawScaleVector.w < drawScaleVector.h) ?
                       drawScaleVector.w : drawScaleVector.h;

        m_type = ObjectType::Camera;
    }

    void Camera::spawn() {
        activate();
    }

    void Camera::despawn() {
        deactivate();
        clear();
    }

    void Camera::onStart() {

    }

    void Camera::onUpdate(float deltaTime) {
        
    }

    void Camera::clear() {
        SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 0);
        SDL_RenderClear(m_renderer.get());
        drawBackground();
    }

    void Camera::drawBackground() {
        SDL_SetRenderDrawColor(m_renderer.get(), m_backgroundColor.r,
                               m_backgroundColor.g, m_backgroundColor.b,
                               m_backgroundColor.a);

        SDL_Rect backgroundRect;
        backgroundRect.x = static_cast<int>((m_windowSize.w / 2) -
                         ((GameConstants::CircleSize.w / 2) * m_drawScale));

        backgroundRect.y = static_cast<int>((m_windowSize.h / 2) -
                         ((GameConstants::CircleSize.h / 2) * m_drawScale));

        backgroundRect.w = static_cast<int>(GameConstants::CircleSize.w *
                                            m_drawScale);

        backgroundRect.h = static_cast<int>(GameConstants::CircleSize.h *
                                            m_drawScale);
                                            
        SDL_RenderFillRect(m_renderer.get(), &backgroundRect);
    }

    void Camera::present() const {
        SDL_RenderPresent(m_renderer.get());
    }

    SDL_Color Camera::getBackgroundColor() const noexcept {
        return m_backgroundColor;
    }

    void Camera::setBackgroundColor(const SDL_Color &color) noexcept {
        m_backgroundColor = color;
    }
    
    SDL_Renderer& Camera::getRenderer() const noexcept {
        return *m_renderer;
    }

    uint32_t Camera::getWindowPixelFormat() const noexcept {
        return m_windowPixelFormat;
    }

    Vector2d<int> Camera::getWindowSize() const noexcept {
        return m_windowSize;
    }

    float Camera::getDrawScale() const noexcept {
        return m_drawScale;
    }
    
} // namespace house
