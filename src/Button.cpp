#include "Button.h"

namespace house {
    
    Button::Button(const std::string &texturePath, Camera &camera,
                   const std::string &name,
                   Vector2d<int> startingPosition,
                   const std::string &tooltipInfo)
    : DrawableObject(texturePath, camera, name, startingPosition, tooltipInfo),
    m_canBeClicked{true},
    m_buttonClickSound{
        AudioManager::loadAudioWav(Button::ButtonClickAudioPath)
    },
    m_onClickConnectedFunction{nullptr}, m_onHoverConnectedFunction{nullptr}
    {
        m_type = ObjectType::Button;
    }

    bool Button::isClicked() {
        if (m_isActive) {
            bool leftDown = (SDL_GetMouseState(NULL, NULL) &
                             SDL_BUTTON(SDL_BUTTON_LEFT));

            if (leftDown && m_canBeClicked) {
                if (isMouseOver()) {
                    m_canBeClicked = false;
                    return true;
                }
                m_canBeClicked = false;
            }

            if (!leftDown) {
                m_canBeClicked = true;
            }
        }

        return false;
    }

    void Button::onSpawn() {
        m_size.w /= 2;
        m_screenSize.w /= 2;
        m_srcDrawRect.w = m_size.w;
        m_srcDrawRect.h = m_size.h;
    }

    void Button::onStart() {
        
    }

    void Button::onUpdate(float deltaTime) {
        if (isMouseOver()) {
            onHover();
        }

        if (isClicked()) {
            onClick();
        }
    }

    void Button::onClick() {
        m_buttonClickSound.play();

        if (isClickConnected()) {
            m_onClickConnectedFunction();
        }
    }

    void Button::onHover() {
        if (isHoverConnected()) {
            m_onHoverConnectedFunction();
        }
    }

    void Button::connectOnClick(std::function<void ()> function) {
        m_onClickConnectedFunction = function;
    }

    void Button::disconnectOnClick() noexcept {
        m_onClickConnectedFunction = nullptr;
    }

    bool Button::isClickConnected() const noexcept {
        return {m_onClickConnectedFunction != nullptr};
    }

    void Button::connectOnHover(std::function<void ()> function) {
        m_onHoverConnectedFunction = function;
    }
    void Button::disconnectOnHover() noexcept {
        m_onHoverConnectedFunction = nullptr;
    }
    bool Button::isHoverConnected() const noexcept {
        return {m_onHoverConnectedFunction != nullptr};
    }

    void Button::draw(Vector2d<int> offset) {
        m_srcDrawRect.x = m_size.w * static_cast<int>(isMouseOver());

        float drawScale = m_camera.getDrawScale();

        auto halfWindowSize = m_camera.getWindowSize() / 2;

        Vector2d<int> drawPos;
        drawPos = halfWindowSize -
                  static_cast<Vector2d<int>>((GameConstants::UICentrePosition -
                                              m_position) * drawScale);
        m_destDrawRect = {drawPos.x, drawPos.y,
                          m_screenSize.w, m_screenSize.h};

        SDL_RendererFlip flip = (m_mirrored) ?
                                 SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderCopyEx(&m_camera.getRenderer(), m_texture.get(),
                         &m_srcDrawRect, &m_destDrawRect, 0, nullptr, flip);
    }

} // namespace house