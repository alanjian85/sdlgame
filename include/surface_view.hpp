#ifndef SDLGAME_SURFACE_VIEW_HPP
#define SDLGAME_SURFACE_VIEW_HPP

#include <SDL2/SDL.h>

namespace sdlgame {
    class surface_view {
    public:
        using native_handle_type = SDL_Surface*;

        surface_view() noexcept : surface_(nullptr) {}
        explicit surface_view(SDL_Surface* surface) noexcept : surface_(surface) {}

        native_handle_type native_handle() const noexcept {
            return surface_;
        }

        Uint32 map_color(Uint8 r, Uint8 g, Uint8 b) noexcept {
            return SDL_MapRGB(surface_->format, r, g, b);
        }

        void fill_rect(Uint32 color) noexcept {
            SDL_FillRect(surface_, nullptr, color);
        }
    protected:
        SDL_Surface* surface_;
    };

    inline void blit_surface(surface_view& src, surface_view& dst) {
        SDL_BlitSurface(src.native_handle(), nullptr, dst.native_handle(), nullptr);
    }
}

#endif