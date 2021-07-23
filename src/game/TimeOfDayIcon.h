#ifndef TIME_OF_DAY_ICON_H
#define TIME_OF_DAY_ICON_H

#include "Image.h"
#include "TimeOfDayEnum.h"

namespace house {

    class TimeOfDayIcon : public Image {
        private:
         static constexpr const char *TexturePath = "gfx\\ui\\timeOfDay.png";
         static constexpr const char *Name        = "Time of day icon";

         void onSpawn();

        public:
         TimeOfDayIcon(Camera &camera, const std::string &tooltipInfo = "");

         void onStart();
         void onUpdate(float deltaTime);

         void changeTimeOfDay(const TimeOfDay &time);

         void scale(float sizeScale) noexcept;
    };
    
} // namespace house

#endif // TIME_OF_DAY_H