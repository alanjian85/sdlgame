#include <iostream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderer.hpp"
#include "sdl.hpp"
#include "surface.hpp"
#include "window.hpp"
using namespace sdlgame;

class game {
public:
    static const auto screen_width = 640;
    static const auto screen_height = 480;

    game()
        : sdl_(SDL_INIT_VIDEO, IMG_INIT_PNG),
          window_("Hello SDL!", screen_width, screen_height, SDL_WINDOW_SHOWN),
          renderer_(window_, -1, SDL_RENDERER_ACCELERATED)
    {
        renderer_.set_draw_color(0xff, 0xff, 0xff, 0xff);
    }

    void load_media() {
        auto loaded_surface = surface::load_image("res/texture.png");
        texture_ = renderer_.create_texture_from_surface(loaded_surface);
    }

    void run() {
        bool quit = false;
        SDL_Event event;

        while (!quit) {
            while (sdl_.poll_event(event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                };
            }

            renderer_.clear();
            renderer_.copy(texture_);
            renderer_.present();
        }
    }
private:
    sdl sdl_;
    window window_;

    renderer renderer_;
    texture texture_;
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