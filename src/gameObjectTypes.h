#ifndef GAME_OBJECT_TYPE_H
#define GAME_OBJECT_TYPE_H
namespace house {

    enum class ObjectType {
        Actor,
        Camera,
        Drawable,
        Object,
        Button,
        Player,
        Enemy,
        Projectile,
        Spikes
    };

} // namespace house

#endif // !GAME_OBJECT_TYPE_H