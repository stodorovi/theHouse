#include "Image.h"

namespace house {
    Image::Image(const std::string &texturePath, Camera &camera,
                 const std::string &name,
                 Vector2d<int> startingPosition,
                 double angle, const std::string &tooltipInfo)
    : DrawableObject(texturePath, camera, name, startingPosition, tooltipInfo),
    m_angle{angle}
    {}

    void Image::onSpawn() {};
    
    void Image::onStart() {};

    void Image::onUpdate(float deltaTime) {};

    double Image::getAngle() const noexcept {
        return m_angle;
    }

    void Image::setAngle(double angle) {
        while (angle > 360.0) {
            angle -= 360.0;
        }

        while (angle < -360.0) {
            angle += 360.0;
        }

        m_angle = angle;
    }

    void Image::draw(Vector2d<int> offset) {
        auto windowSize     = m_camera.getWindowSize();
        auto halfWindowSize = windowSize / 2;
        auto drawScale      = m_camera.getDrawScale();

        Vector2d<int> drawDestVector = halfWindowSize -
                                     ((GameConstants::UICentrePosition -
                                       m_position + offset) * drawScale) -
                                       (m_screenSize / 2);
        m_destDrawRect = {drawDestVector.x, drawDestVector.y,
                          m_screenSize.w, m_screenSize.h};

        SDL_Point centrePoint {m_screenSize.x / 2, m_screenSize.y / 2};

        SDL_RendererFlip flip = (m_mirrored) ?
                                 SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderCopyEx(&m_camera.getRenderer(), m_texture.get(),
                         &m_srcDrawRect, &m_destDrawRect,
                          m_angle, &centrePoint, flip);
    }

} // namespace house