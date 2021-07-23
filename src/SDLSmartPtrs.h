#ifndef GAME_SDL_SMART_PTRS_H
#define GAME_SDL_SMART_PTRS_H

#include <memory>

#include "SDL.h"
#include "SDL_mixer.h"

namespace house {

    struct SDL_deleter {
        void operator()(SDL_Window *ptr) {
            SDL_DestroyWindow(ptr);
        }
        void operator()(SDL_Renderer *ptr) {
            SDL_DestroyRenderer(ptr);
        }
        void operator()(SDL_Texture *ptr) {
            SDL_DestroyTexture(ptr);
        }
        void operator()(Mix_Chunk *ptr) {
            Mix_FreeChunk(ptr);
        }
    };

    class SDL_Window_unique_ptr
        : public std::unique_ptr<SDL_Window, SDL_deleter>
    {
        public:
         SDL_Window_unique_ptr (SDL_Window *ptr)
            : std::unique_ptr<SDL_Window, SDL_deleter> (ptr)
         {}
    };

    class SDL_Renderer_unique_ptr
        : public std::unique_ptr<SDL_Renderer, SDL_deleter>
    {
        public:
         SDL_Renderer_unique_ptr(SDL_Renderer *ptr)
            : std::unique_ptr<SDL_Renderer, SDL_deleter>(ptr)
         {}
    };

    class SDL_Texture_unique_ptr
        : public std::unique_ptr<SDL_Texture, SDL_deleter>
    {
        public:
         SDL_Texture_unique_ptr(SDL_Texture *ptr)
            : std::unique_ptr<SDL_Texture, SDL_deleter>(ptr)
         {}
    };

    class Mix_Chunk_unique_ptr
        : public std::unique_ptr<Mix_Chunk, SDL_deleter>
    {
        public:
         Mix_Chunk_unique_ptr(Mix_Chunk *ptr)
            : std::unique_ptr<Mix_Chunk, SDL_deleter>(ptr)
         {}

         void play() {
            if (get()) Mix_PlayChannel(-1, get(), 0);
         }
    };

} // namespace house

#endif // !GAME_SDL_SMART_PTRS_H
