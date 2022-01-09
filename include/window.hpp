#ifndef SDLGAME_WINDOW_HPP
#define SDLGAME_WINDOW_HPP

#include <algorithm>
#include <string>
#include <system_error>

#include <SDL2/SDL.h>

#include "weak_surface.hpp"

namespace sdlgame {
    class window final {
    public:
        using surface_type = weak_surface;

        window() noexcept : window_(nullptr) {}
        
        window(const char* title, int w, int h, Uint32 flag) {
            window_ = SDL_CreateWindow(
                title,
                SDL_WINDOWPOS_UNDEFINED, 
                SDL_WINDOWPOS_UNDEFINED, 
                w,
                h,
                flag
            );

            if (!window_) {
                throw std::system_error(std::error_code(), std::string("Window could not be created! SDL_Error: ") + SDL_GetError());
            }
        }

        window(window&& rhs) noexcept {
            window_ = std::exchange(rhs.window_, nullptr);
        }

        window& operator=(window&& rhs) noexcept {
            SDL_DestroyWindow(window_);
            window_ = std::exchange(rhs.window_, nullptr);
            return *this;
        }

        ~window() noexcept {
            SDL_DestroyWindow(window_);
        }

        operator bool() const noexcept {
            return window_;
        }

        weak_surface get_surface() const noexcept {
            return weak_surface(SDL_GetWindowSurface(window_));
        }

        void update_surface() noexcept {
            SDL_UpdateWindowSurface(window_);
        }
    private:
        SDL_Window* window_;
    };
}

#endif