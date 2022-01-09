#ifndef SDLGAME_SURFACE_HPP
#define SDLGAME_SURFACE_HPP

#include <SDL2/SDL.h>

namespace sdlgame {
    class surface final {
    public:
        using native_handle_type = SDL_Surface*;

        static surface load_bmp(const char* file) noexcept {
            return surface(SDL_LoadBMP(file));            
        }

        surface() noexcept : surface_(nullptr) {}
        explicit surface(SDL_Surface* surface) noexcept : surface_(surface) {}

        ~surface() noexcept {
            SDL_FreeSurface(surface_);
        }

        native_handle_type native_handle() const noexcept {
            return surface_;
        }

        Uint32 map_color(Uint8 r, Uint8 g, Uint8 b) noexcept {
            return SDL_MapRGB(surface_->format, r, g, b);
        }

        void fill_rect(Uint32 color) noexcept {
            SDL_FillRect(surface_, nullptr, color);
        }
    private:
        SDL_Surface* surface_;
    };

    inline void blit_surface(surface& src, surface& dst) {
        SDL_BlitSurface(src.native_handle(), nullptr, dst.native_handle(), nullptr);
    }
}

#endif