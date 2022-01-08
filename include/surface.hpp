#ifndef SDLGAME_SURFACE_HPP
#define SDLGAME_SURFACE_HPP

#include <SDL2/SDL.h>

namespace sdlgame {
    class surface final {
    public:
        surface() noexcept : surface_(nullptr) {}
        explicit surface(SDL_Surface* surface) noexcept : surface_(surface) {}

        Uint32 map_color(Uint8 r, Uint8 g, Uint8 b) noexcept {
            return SDL_MapRGB(surface_->format, r, g, b);
        }

        void fill_rect(Uint32 color) noexcept {
            SDL_FillRect(surface_, nullptr, color);
        }
    private:
        SDL_Surface* surface_;
    };
}

#endif