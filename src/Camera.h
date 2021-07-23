#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include "SDL.h"
#include "SDLSmartPtrs.h"

#include "GameObject.h"

namespace house {

    class Camera : public GameObject {
        private:
         SDL_Renderer_unique_ptr m_renderer;
         SDL_Color m_backgroundColor;
         uint32_t m_windowPixelFormat;

         Vector2d<int> m_windowSize;

         float m_drawScale;

        public:
         Camera(SDL_Window &window, const SDL_Color &backgroundColor,
                const std::string &name = "Camera");

         void spawn();
         void despawn();
        
         void onStart();
         void onUpdate(float deltaTime);

         void clear();
         void drawBackground();
         void present() const;

         SDL_Renderer& getRenderer() const noexcept;

         SDL_Color getBackgroundColor() const noexcept;
         void setBackgroundColor(const SDL_Color &color) noexcept;

         uint32_t getWindowPixelFormat() const noexcept;

         Vector2d<int> getWindowSize() const noexcept;

         float getDrawScale() const noexcept;
    };
} // namespace house

#endif // !CAMERA_H