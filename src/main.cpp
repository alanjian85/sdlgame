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

    }

    void load_media() {
        auto background_surface = surface::load_image("res/background.png");
        background_texture_ = renderer_.create_texture(background_surface);

        auto foo_surface = surface::load_image("res/foo.png");
        foo_surface.set_color_key(foo_surface.map_color(0, 0xff, 0xff));
        foo_texture_ = renderer_.create_texture(foo_surface);
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

            renderer_.set_draw_color(0xff, 0xff, 0xff, 0xff);
            renderer_.clear();

            renderer_.copy(background_texture_, 0, 0);

            renderer_.present();
        }
    }
private:
    sdl sdl_;
    window window_;

    renderer renderer_;
    texture foo_texture_;
    texture background_texture_;
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