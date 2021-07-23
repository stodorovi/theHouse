#include "TimeOfDayIcon.h"

namespace house {
    
    TimeOfDayIcon::TimeOfDayIcon(Camera &camera, const std::string &tooltipInfo)
    : Image(TexturePath, camera, Name,
            GameConstants::UICentrePosition, 0.0, tooltipInfo)
    {}

    void TimeOfDayIcon::onSpawn() {
        m_size.w /= 3;
        m_screenSize.w /= 3;
        m_srcDrawRect.w = m_size.w;

        m_position = GameConstants::UICentrePosition -
                    (GameConstants::CircleSize / 2) +
                    m_size * (2.0f / 3);
   }

    void TimeOfDayIcon::onStart() {
        
    }

    void TimeOfDayIcon::onUpdate(float deltaTime) {

    }

    void TimeOfDayIcon::changeTimeOfDay(const TimeOfDay &time) {
        m_srcDrawRect.x = static_cast<int>(time) * m_size.w;
    }

    void TimeOfDayIcon::scale(float sizeScale) noexcept {
        m_screenSize *= sizeScale;
    }

} // namespace house