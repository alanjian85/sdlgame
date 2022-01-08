#ifndef SDLGAME_WINDOW_HPP
#define SDLGAME_WINDOW_HPP

#include <system_error>

#include <SDL2/SDL.h>

#include "surface.hpp"

namespace sdlgame {
    class window final {
    public:
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
                throw std::system_error(std::error_code(), SDL_GetError());
            }
        }

        ~window() {
            SDL_DestroyWindow(window_);
        }

        operator bool() const noexcept {
            return window_;
        }

        surface get_surface() const noexcept {
            return surface(SDL_GetWindowSurface(window_));
        }

        void update_surface() noexcept {
            SDL_UpdateWindowSurface(window_);
        }
    private:
        SDL_Window* window_;
    };
}

#endif