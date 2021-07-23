#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include "SDLSmartPtrs.h"

#include "TextureManager.h"
#include "AudioManager.h"
#include "GameObject.h"
#include "Camera.h"

namespace house {

    class DrawableObject : public GameObject {
        private:
         const Vector2d<int> m_startingPosition;
        
        protected:
         SDL_Texture_unique_ptr m_texture;
         std::string m_texturePath;

         Camera &m_camera;

         Vector2d<int> m_size;
         Vector2d<int> m_screenSize;

         SDL_Rect m_srcDrawRect;
         SDL_Rect m_destDrawRect;

         bool m_spawned;

         std::string m_tooltipInfo;

         virtual void onSpawn() = 0;

        public:
         DrawableObject(const std::string &texturePath, Camera &camera,
                        const std::string &name = "DrawableObject",
                        Vector2d<int> startingPosition = {0, 0},
                        const std::string &tooltipInfo = "");

         virtual void spawn();
         void despawn();

         Vector2d<int> getSize() const noexcept;

         Vector2d<int> getScreenSize() const noexcept;

         bool isMouseOver() const noexcept;

         bool isSpawned() const noexcept;

         const std::string& getTooltipInfo() const noexcept;
         
         /**
          * \brief Sets the tooltip info text.
          *        Can't be longer than 200 characters.
          * \return Returns 1 of success, 0 if text can not be set.
          **/
         int setTooltipInfo(const std::string &text) noexcept;

         virtual void draw(Vector2d<int> offset = {0, 0}) = 0;
    };
    
} // namespace house

#endif // !DRAWABLE_OBJECT_H