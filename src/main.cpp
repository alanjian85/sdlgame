#include <iostream>

#include <SDL2/SDL.h>

const auto screen_width = 640;
const auto screen_height = 480;

int main() {
    SDL_Window* window = nullptr;
    SDL_Surface* screen_surface = nullptr;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
    } else {
        window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        } else {
            screen_surface = SDL_GetWindowSurface(window);

            SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format, 0xff, 0xff, 0xff));
            SDL_UpdateWindowSurface(window);

            SDL_Delay(2000);
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}