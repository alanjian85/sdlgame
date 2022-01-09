#ifndef SDLGAME_SDL_HPP
#define SDLGAME_SDL_HPP

#include <string>
#include <system_error>

#include <SDL2/SDL.h>

namespace sdlgame {
    class sdl final {
    public:
        sdl(const sdl&) = delete;
        sdl& operator=(const sdl&) = delete;

        explicit sdl(Uint32 flags) {
            auto status = SDL_Init(flags);
            if (status < 0) {
                throw std::system_error(std::error_code(status, std::system_category()),
                                        std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
            }
        }

        ~sdl() noexcept {
            SDL_Quit();
        }

        void delay(Uint32 ms) const noexcept {
            SDL_Delay(ms);
        }
    };
}

#endif