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

            SDL_Rect fill_rect = {screen_width / 4, screen_height / 4, screen_width / 2, screen_height / 2};
            renderer_.set_draw_color(0xff, 0x00, 0x00, 0xff);
            renderer_.fill_rect(fill_rect);

            SDL_Rect outline_rect = {screen_width / 6, screen_height / 6, screen_width * 2 / 3, screen_height * 2 / 3};
            renderer_.set_draw_color(0x00, 0xff, 0x00, 0xff);
            renderer_.draw_rect(outline_rect);

            renderer_.set_draw_color(0x00, 0x00, 0xff, 0xff);
            renderer_.draw_line(0, screen_height / 2, screen_width, screen_height / 2);

            renderer_.set_draw_color(0xff, 0xff, 0x00, 0xff);
            for (int i = 0; i < screen_height; i += 4) {
                renderer_.draw_point(screen_width / 2, i);
            }

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