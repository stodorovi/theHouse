#ifndef WIZARDS_PROJECTILE_H
#define WIZARDS_PROJECTILE_H

#include "Actor.h"

namespace house {
    
    class WizardsProjectile : public Actor {
        private:
         static constexpr const char *Name
                                    = "Wizard's Projectile";
         static constexpr const char *TexturePath
                                    = "gfx\\objects\\wizardsProjectile.png";

         int m_attackPower;

         Direction m_moveDirection;

         static constexpr SDL_Rect m_sidewaysSrcRect  {0,  0,  6, 20};
         static constexpr SDL_Rect m_upwardsSrcRect   {6,  0, 20,  6};
         static constexpr SDL_Rect m_downwardsSrcRect {6, 14, 20,  6};

         void onStart();
         void onSpawn();
         void onUpdate(float deltaTime);
        
        public:
         WizardsProjectile(Camera &camera,
                          Vector2d<int> startingPosition,
                          int attackPower,
                          Direction direction = Direction::Right);


         void onCollision(const Actor &other);

         int getAttackPower() const noexcept;
    };

} // namespace house

#endif // !WIZARDS_PROJECTILE_H