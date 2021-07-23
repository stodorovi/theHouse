#include "Actor.h"
namespace house {
    
    Actor::Actor(const std::string &texturePath, Camera &camera,
                 const std::string &name, Vector2d<int> startingPosition,
                 bool collision, const std::string &tooltipInfo)
    :DrawableObject(texturePath, camera, name, startingPosition, tooltipInfo),
    m_collidable {collision}
    {
        m_type = ObjectType::Actor;
    }

    Actor::Actor(Camera &camera, const std::string &name,
                 Vector2d<int> startingPosition,
                 Vector2d<int> size, bool collision,
                 const std::string &tooltipInfo)
    : DrawableObject("", camera, name, startingPosition, tooltipInfo),
    m_collidable {collision}
    {
        m_size = size;
        m_screenSize = m_size * m_camera.getDrawScale();
        m_srcDrawRect = {0, 0, m_size.w, m_size.h};
    }

    bool Actor::isCollidable() const noexcept {
        return m_collidable;
    }

    void Actor::activateCollision() noexcept {
        m_collidable = true;
    }
    
    void Actor::deactivateCollision() noexcept {
        m_collidable = false;
    }

    bool Actor::isCollidingWith(const Actor &other) const {
        auto otherPosition = other.getPosition();
        auto otherSize     = other.getSize();

        int leftXpos  = static_cast<int>(m_position.x);
        int rightXpos = static_cast<int>(m_position.x) + m_size.w;
        int upYpos    = static_cast<int>(m_position.y);
        int downYpos  = static_cast<int>(m_position.y) + m_size.h;
        
        int otherLeftXpos  = static_cast<int>(otherPosition.x);
        int otherRightXpos = static_cast<int>(otherPosition.x) + otherSize.w;
        int otherUpYpos    = static_cast<int>(otherPosition.y);
        int otherDownYpos  = static_cast<int>(otherPosition.y) + otherSize.h;

        bool leftSideInside  = leftXpos <= otherRightXpos &&
                               leftXpos >= otherLeftXpos;
        bool rightSideInside = rightXpos >= otherLeftXpos &&
                               rightXpos <= otherRightXpos;
        bool upSideInside    = upYpos <= otherDownYpos &&
                               upYpos >= otherUpYpos;
        bool downSideInside  = downYpos >= otherUpYpos &&
                               downYpos <= otherDownYpos;

        bool thisInsideOther = (leftSideInside || rightSideInside) &&
                               (upSideInside || downSideInside);

        bool otherLeftSideInside  = otherLeftXpos <= rightXpos &&
                                    otherLeftXpos >= leftXpos;
        bool otherRightSideInside = otherRightXpos >= leftXpos &&
                                    otherRightXpos <= rightXpos;
        bool otherUpSideInside    = otherUpYpos <= downYpos &&
                                    otherUpYpos >= upYpos;
        bool otherDownSideInside  = otherDownYpos >= upYpos &&
                                    otherDownYpos <= downYpos;

        bool otherInsideThis = (otherLeftSideInside || otherRightSideInside) &&
                               (otherUpSideInside || otherDownSideInside);

        return {thisInsideOther || otherInsideThis};
    }

    void Actor::handleCollision(const Actor &other) {
        if (isCollidingWith(other)) {
            float leftBorderInsideLength = m_position.x + m_size.w -
                                           other.getPosition().x;
            leftBorderInsideLength *= static_cast<float>(
                                                leftBorderInsideLength > 0);

            float rightBorderInsideLength = other.getPosition().x +
                                            other.getSize().w - m_position.x;
            rightBorderInsideLength *= static_cast<float>(
                                                rightBorderInsideLength > 0);
                                      
            float topBorderInsideLength = m_position.y + m_size.h -
                                          other.getPosition().y;
            topBorderInsideLength *= static_cast<float>(
                                                topBorderInsideLength > 0);

            float bottomBorderInsideLength = other.getPosition().y +
                                             other.getSize().h - m_position.y;
            bottomBorderInsideLength *= static_cast<float>(
                                                bottomBorderInsideLength > 0);

            if ((leftBorderInsideLength < topBorderInsideLength &&
                 leftBorderInsideLength < bottomBorderInsideLength) &&
                 leftBorderInsideLength > 0)
            {
                m_position.x -= leftBorderInsideLength;
            }
            else if ((rightBorderInsideLength < topBorderInsideLength &&
                      rightBorderInsideLength < bottomBorderInsideLength) &&
                      rightBorderInsideLength > 0) 
            {
                m_position.x += rightBorderInsideLength;
            }

            else if ((topBorderInsideLength < leftBorderInsideLength &&
                      topBorderInsideLength < rightBorderInsideLength) &&
                      topBorderInsideLength > 0)
            {
                m_position.y -= topBorderInsideLength;
            }
            else if ((bottomBorderInsideLength < leftBorderInsideLength &&
                      bottomBorderInsideLength < rightBorderInsideLength) &&
                      bottomBorderInsideLength > 0)
            {
                m_position.y += bottomBorderInsideLength;
            }

            onCollision(other);
        }
    }

    void Actor::draw(Vector2d<int> offset) {
        auto cameraPosition = m_camera.getPosition();

        auto halfWindowSize = m_camera.getWindowSize() / 2;
        float drawScale = m_camera.getDrawScale();

        Vector2d<int> drawDestVector = (((m_position + offset) -
                                          cameraPosition) * drawScale) +
                                          halfWindowSize;

        m_destDrawRect = {drawDestVector.x, drawDestVector.y,
                          m_screenSize.w, m_screenSize.h};

        SDL_RendererFlip flip = (m_mirrored) ?
                                SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        SDL_RenderCopyEx(&m_camera.getRenderer(), m_texture.get(),
                         &m_srcDrawRect, &m_destDrawRect, 0, nullptr, flip);
   }

    void Actor::draw(SDL_Texture &texture, Vector2d<int> offset) {
        auto cameraPosition = m_camera.getPosition();

        auto halfWindowSize = m_camera.getWindowSize() / 2;
        float drawScale = m_camera.getDrawScale();

        Vector2d<int> drawDestVector = (((m_position + offset) -
                                          cameraPosition) * drawScale) +
                                          halfWindowSize;

        m_destDrawRect = {drawDestVector.x, drawDestVector.y,
                          m_screenSize.w, m_screenSize.h};

        SDL_RenderCopyEx(&m_camera.getRenderer(), &texture, &m_srcDrawRect,
                         &m_destDrawRect, 0, nullptr, SDL_FLIP_NONE);
    }

} // namespace house