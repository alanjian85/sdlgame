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
        window_ = window("Hello SDL!", screen_width, screen_height, SDL_WINDOW_SHOWN);
        screen_surface_ = window_.get_surface();
    }

    void load_media() {
        x_out_ = surface::load_bmp("res/x.bmp");
    }

    void run() {
        bool quit = false;
        SDL_Event event;

        while (!quit) {
            while (SDL_PollEvent(&event) == 1) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
            }

            blit_surface(x_out_, screen_surface_);
            window_.update_surface();
        }
    }
private:
    sdl sdl_;
    window window_;
    window::surface_type screen_surface_;
    surface x_out_;
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