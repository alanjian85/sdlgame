#include <iostream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl.hpp"
#include "surface.hpp"
#include "window.hpp"
using namespace sdlgame;

class game {
public:
    static const auto screen_width = 640;
    static const auto screen_height = 480;

    game()
        : sdl_(SDL_INIT_VIDEO, IMG_INIT_PNG)
    {
        window_ = window("Hello SDL!", screen_width, screen_height, SDL_WINDOW_SHOWN);
        screen_surface_ = window_.get_surface();
    }

    void load_media() {
        auto loaded_surface = surface::load_image("res/loaded.png");
        optimized_surface_ = loaded_surface.convert(screen_surface_.format(), 0);    
    }

    void run() {
        bool quit = false;
        SDL_Event event;

        while (!quit) {
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                };
            }

            SDL_Rect stretch_rect;
            stretch_rect.x = 0;
            stretch_rect.y = 0;
            stretch_rect.w = screen_width;
            stretch_rect.h = screen_height;
            blit_scaled(optimized_surface_, screen_surface_, stretch_rect);
            window_.update_surface();
        }
    }
private:
    sdl sdl_;
    window window_;
    surface_view screen_surface_;

    surface optimized_surface_;
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