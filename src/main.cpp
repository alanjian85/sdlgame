#include <iostream>

#include <SDL2/SDL.h>

#include "sdl.hpp"
#include "surface.hpp"
#include "window.hpp"

const auto screen_width = 640;
const auto screen_height = 480;

using namespace sdlgame;

int main() {
    try {
        sdl s(SDL_INIT_VIDEO);
        auto w = window("Hello SDL!", screen_width, screen_height, SDL_WINDOW_SHOWN);
        auto screen_surface = w.get_surface();

        screen_surface.fill_rect(screen_surface.map_color(0xff, 0xff, 0xff));
        w.update_surface();

        SDL_Delay(2000);
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}