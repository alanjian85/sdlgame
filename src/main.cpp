#include <iostream>
#include <map>

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
        key_press_surfaces[SDLK_UP] = surface::load_bmp("res/up.bmp");
        key_press_surfaces[SDLK_DOWN] = surface::load_bmp("res/down.bmp");
        key_press_surfaces[SDLK_LEFT] = surface::load_bmp("res/left.bmp");
        key_press_surfaces[SDLK_RIGHT] = surface::load_bmp("res/right.bmp"); 
        key_press_surfaces[SDLK_UNKNOWN] = surface::load_bmp("res/press.bmp");
    }

    void run() {
        bool quit = false;
        SDL_Event event;

        while (!quit) {
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            current_surface_ = key_press_surfaces[SDLK_UP];
                            break;
                        case SDLK_DOWN:
                            current_surface_ = key_press_surfaces[SDLK_DOWN];
                            break;
                        case SDLK_LEFT:
                            current_surface_ = key_press_surfaces[SDLK_LEFT];
                            break;
                        case SDLK_RIGHT:
                            current_surface_ = key_press_surfaces[SDLK_RIGHT];
                            break;
                        default:
                            current_surface_ = key_press_surfaces[SDLK_UNKNOWN];
                            break;
                    }
                }
            }

            blit_surface(current_surface_, screen_surface_);
            window_.update_surface();
        }
    }
private:
    sdl sdl_;
    window window_;
    window::surface_type screen_surface_;

    std::map<SDL_Keycode, surface> key_press_surfaces;
    surface_view current_surface_;
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