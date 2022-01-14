#ifndef SDLGAME_RENDERER_HPP
#define SDLGAME_RENDERER_HPP

#include <algorithm>
#include <string>
#include <system_error>

#include <SDL2/SDL.h>

#include "texture.hpp"
#include "window.hpp"

namespace sdlgame {
    class renderer final {
    public:
        renderer() noexcept : renderer_(nullptr) {}

        renderer(const window& w, int index, Uint32 flags) noexcept {
            renderer_ = SDL_CreateRenderer(w.native_handle(), index, flags);
            if (!renderer_) {
                throw std::system_error(std::error_code(), std::string("Renderer could not be created! SDL Error: ") + SDL_GetError());
            }
        }

        renderer(renderer&& rhs) noexcept {
            renderer_ = std::exchange(rhs.renderer_, nullptr);
        }

        renderer& operator=(renderer&& rhs) noexcept {
            SDL_DestroyRenderer(renderer_);
            renderer_ = std::exchange(rhs.renderer_, nullptr);
            return *this;
        }

        ~renderer() noexcept {
            SDL_DestroyRenderer(renderer_);
        }

        void set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) noexcept {
            SDL_SetRenderDrawColor(renderer_, r, g, b, a);
        }

        texture create_texture(surface_view s) noexcept {
            return texture(SDL_CreateTextureFromSurface(renderer_, s.native_handle()), s.width(), s.height());
        }

        void clear() noexcept {
            SDL_RenderClear(renderer_);
        }

        void present() noexcept {
            SDL_RenderPresent(renderer_);
        }

        void copy(const texture& tex) noexcept {
            SDL_RenderCopy(renderer_, tex.native_handle(), nullptr, nullptr);
        }

        void copy(const texture& tex, SDL_Rect dstrect) noexcept {
            SDL_RenderCopy(renderer_, tex.native_handle(), nullptr, &dstrect);
        }

        void fill_rect(SDL_Rect rect) noexcept {
            SDL_RenderFillRect(renderer_, &rect);
        }

        void draw_rect(SDL_Rect rect) noexcept {
            SDL_RenderDrawRect(renderer_, &rect);
        }

        void draw_line(int x1, int y1, int x2, int y2) noexcept {
            SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
        }

        void draw_point(int x, int y) noexcept {
            SDL_RenderDrawPoint(renderer_, x, y);
        }

        void set_viewport(SDL_Rect rect) noexcept {
            SDL_RenderSetViewport(renderer_, &rect);
        }
    protected:
        SDL_Renderer* renderer_;
    };
}

#endif