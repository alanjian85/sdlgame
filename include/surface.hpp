#ifndef SDLGAME_SURFACE_HPP
#define SDLGAME_SURFACE_HPP

#include <algorithm>
#include <string>
#include <system_error>

#include <SDL2/SDL.h>

#include "weak_surface.hpp"

namespace sdlgame {
    class surface final : public weak_surface {
    public:
        static surface load_bmp(const char* file) {
            auto s = SDL_LoadBMP(file);
            if (!s) {
                throw std::system_error(std::error_code(), std::string("Unable to load image ") + file + "! SDL_Error: " + SDL_GetError());
            }
            return surface(s);
        }

        using weak_surface::weak_surface;

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
    };
}

#endif