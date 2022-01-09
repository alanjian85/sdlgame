#include <iostream>

#include <SDL2/SDL.h>

#include "sdl.hpp"
#include "surface.hpp"
#include "window.hpp"
using namespace sdlgame;

class game {
public:
    static const auto screen_width = 640;
    static const auto screen_height = 480;

    game()
        : sdl_(SDL_INIT_VIDEO)
    {
        window_ = window("Hello SDL!", screen_width, screen_width, SDL_WINDOW_SHOWN);
        screen_surface_ = window_.get_surface();
    }

    void load_media() {
        hello_world_ = surface::load_bmp("res/hello_world.bmp");
    }

    void run() {
        blit_surface(hello_world_, screen_surface_);
        window_.update_surface();
        sdl_.delay(2000);
    }
private:
    sdl sdl_;
    window window_;
    window::surface_type screen_surface_;
    surface hello_world_;
};

int main() {
    try {
        game g;
        g.load_media();
        g.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}