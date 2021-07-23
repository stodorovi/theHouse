#ifndef BUTTON_H
#define BUTTON_H

#include "DrawableObject.h"
#include <functional>

namespace house {

    class Button : public DrawableObject {
        protected:
         bool m_canBeClicked;

         Mix_Chunk_unique_ptr m_buttonClickSound;

         static constexpr const char *ButtonClickAudioPath
                                                = "sfx\\ui\\buttonClick.wav";

         void onSpawn();

         bool isClicked();

         std::function<void ()> m_onClickConnectedFunction;
         std::function<void ()> m_onHoverConnectedFunction;

        public:
         Button(const std::string &texturePath, Camera &camera,
                const std::string &name = "Button",
                Vector2d<int> startingPosition = {0, 0},
                const std::string &tooltipInfo = "");

         void onStart();
         void onUpdate(float deltaTime);

         void onHover();
         void onClick();

         void connectOnClick(std::function<void ()> function);
         void disconnectOnClick() noexcept;
         bool isClickConnected() const noexcept;

         void connectOnHover(std::function<void ()> function);
         void disconnectOnHover() noexcept;
         bool isHoverConnected() const noexcept;

         void draw(Vector2d<int> offset = {0, 0});
    };

} // namespace house

#endif // !BUTTON_H