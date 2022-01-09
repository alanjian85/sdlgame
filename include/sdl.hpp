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

        explicit sdl(Uint32 sdl_flags, Uint32 image_flags) {
            auto sdl_status = SDL_Init(sdl_flags);
            if (sdl_status < 0) {
                throw std::system_error(std::error_code(sdl_status, std::system_category()),
                                        std::string("SDL could not initialize! SDL Error: ") + SDL_GetError());
            }

            auto image_status = IMG_Init(image_flags);
            if (!(image_status & image_flags)) {
                throw std::system_error(std::error_code(image_status, std::system_category()),
                                        std::string("SDL_image could not initialize! SDL_image Error: ") + SDL_GetError());
            }
        }

        ~sdl() noexcept {
            SDL_Quit();
        }

        void delay(Uint32 ms) const noexcept {
            SDL_Delay(ms);
        }

        bool poll_event(SDL_Event& event) noexcept {
            return SDL_PollEvent(&event) != 0;
        }
    };
}

#endif