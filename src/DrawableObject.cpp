#include "DrawableObject.h"

namespace house {
    DrawableObject::DrawableObject(const std::string &texturePath,
                                   Camera &camera, const std::string &name,
                                   Vector2d<int> startingPosition,
                                   const std::string &tooltipInfo)
    : GameObject(name, startingPosition), m_startingPosition{startingPosition},
    m_texture {nullptr}, m_texturePath{texturePath}, m_camera {camera},
    m_size{0, 0}, m_screenSize{0, 0}, m_srcDrawRect{0, 0, 0, 0},
    m_spawned{false}, m_destDrawRect{0, 0, 0, 0}, m_tooltipInfo{tooltipInfo}
    {
        m_type = ObjectType::Drawable;
    }

    void DrawableObject::spawn() {
        if (!m_texturePath.empty()) {
            auto *renderer = &m_camera.getRenderer();
            m_texture.reset(TextureManager::loadTexture(renderer,
                                                        m_texturePath));
            
            auto format = m_camera.getWindowPixelFormat();
            SDL_QueryTexture(m_texture.get(), &format, NULL,
                            &m_size.w, &m_size.h);
            m_srcDrawRect = {0, 0, m_size.w, m_size.h};

            m_screenSize = m_size * m_camera.getDrawScale();

            onSpawn();
        }
    
        m_spawned = true;
        activate();
    }

    void DrawableObject::despawn() {
        m_texture.reset(nullptr);
        m_position = m_startingPosition;
        m_spawned = false;
        deactivate();
    }

    bool DrawableObject::isMouseOver() const noexcept {
        if (m_isActive) {
            Vector2d<int> mousePosition;
            SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

            auto &screenPosition = m_destDrawRect;
            bool mouseInsideX = mousePosition.x >= screenPosition.x &&
                                mousePosition.x < (screenPosition.x +
                                                   m_screenSize.w);

            bool mouseInsideY = mousePosition.y >= screenPosition.y &&
                                mousePosition.y < (screenPosition.y +
                                                   m_screenSize.h);

            return {mouseInsideX && mouseInsideY};
        }

        return false;
    }

    bool DrawableObject::isSpawned() const noexcept {
        return m_spawned;
    }

    const std::string& DrawableObject::getTooltipInfo() const noexcept {
        return m_tooltipInfo;
    }

    int DrawableObject::setTooltipInfo(const std::string &text) noexcept {
        if (text.size() < 200) {
            m_tooltipInfo = text;
            return true;
        }
        
        return false;
    }

    Vector2d<int> DrawableObject::getSize() const noexcept {
        return m_size;
    }

    Vector2d<int> DrawableObject::getScreenSize() const noexcept {
        return m_screenSize;
    }

} // namespace house