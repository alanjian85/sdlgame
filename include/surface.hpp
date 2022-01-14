#ifndef SDLGAME_SURFACE_HPP
#define SDLGAME_SURFACE_HPP

#include <algorithm>
#include <string>
#include <system_error>

#include <SDL2/SDL.h>

namespace sdlgame {
    class surface;

    class surface_view {
    public:
        using native_handle_type = SDL_Surface*;

        surface_view() noexcept : surface_(nullptr) {}
        explicit surface_view(SDL_Surface* surface) noexcept : surface_(surface) {}

        native_handle_type native_handle() const noexcept {
            return surface_;
        }

        const SDL_PixelFormat* format() const noexcept {
            return surface_->format;
        }

        Uint32 map_color(Uint8 r, Uint8 g, Uint8 b) noexcept {
            return SDL_MapRGB(surface_->format, r, g, b);
        }

        void fill_rect(Uint32 color) noexcept {
            SDL_FillRect(surface_, nullptr, color);
        }

        surface convert(const SDL_PixelFormat* format, Uint32 flags) const noexcept;
    
        void set_color_key(Uint32 key) noexcept {
            SDL_SetColorKey(surface_, SDL_TRUE, key);
        }
    
        int width() const noexcept {
            return surface_->w;
        }

        int height() const noexcept {
            return surface_->h;
        }
    protected:
        SDL_Surface* surface_;
    };

    inline void blit_surface(surface_view& src, surface_view& dst) noexcept {
        SDL_BlitSurface(src.native_handle(), nullptr, dst.native_handle(), nullptr);
    }

    inline void blit_scaled(surface_view& src, surface_view& dst, SDL_Rect rect) noexcept {
        SDL_BlitScaled(src.native_handle(), nullptr, dst.native_handle(), &rect);
    }

    class surface final : public surface_view {
    public:
        static surface load_bmp(const char* file) {
            auto s = SDL_LoadBMP(file);
            if (!s) {
                throw std::system_error(std::error_code(), std::string("Unable to load BMP ") + file + "! SDL Error: " + SDL_GetError());
            }
            return surface(s);
        }

        static surface load_image(const char* file) {
            auto s = IMG_Load(file);
            if (!s) {
                throw std::system_error(std::error_code(), std::string("Unable to load image ") + file + "! SDL_image Error: " + SDL_GetError());
            }
            return surface(s);
        }

        using surface_view::surface_view;

        surface(surface&& rhs) noexcept {
            surface_ = std::exchange(rhs.surface_, nullptr);
        }

        surface& operator=(surface&& rhs) noexcept {
            SDL_FreeSurface(surface_);
            surface_ = std::exchange(rhs.surface_, nullptr);
            return *this;
        }

        ~surface() noexcept {
            SDL_FreeSurface(surface_);
        }

        void destroy() noexcept {
            SDL_FreeSurface(surface_);
            surface_ = nullptr;
        }
    };

    inline surface surface_view::convert(const SDL_PixelFormat* format, Uint32 flags) const noexcept {
        return surface(SDL_ConvertSurface(surface_, format, flags));
    }
}

#endif