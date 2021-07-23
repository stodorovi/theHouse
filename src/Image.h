#ifndef IMAGE_H
#define IMAGE_H

#include "DrawableObject.h"

namespace house {

    class Image : public DrawableObject {
        protected:
         double m_angle;

         void onSpawn();

        public:
         Image(const std::string &texturePath, Camera &camera,
               const std::string &name = "Image",
               Vector2d<int> startingPosition = GameConstants::UICentrePosition,
               double angle = 0.0, const std::string &tooltipInfo = "");

         void onStart();
         void onUpdate(float deltaTime);

         double getAngle() const noexcept;
         void setAngle(double angle);
        
         void draw(Vector2d<int> offset = {0, 0});
    };

} // namespace house

#endif // !IMAGE_H