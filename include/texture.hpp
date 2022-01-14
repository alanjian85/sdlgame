#ifndef SDLGAME_TEXTURE_HPP
#define SDLGAME_TEXTURE_HPP

#include <algorithm>

#include <SDL2/SDL.h>

namespace sdlgame {
    class texture final {
    public:
        using native_handle_type = SDL_Texture*;

        texture() noexcept : texture_(nullptr), width_(0), height_(0) {}

        explicit texture(SDL_Texture* tex, int width, int height) noexcept 
            : texture_(tex),
              width_(width),
              height_(height) 
        {

        }

        texture(texture&& rhs) noexcept {
            texture_ = std::exchange(rhs.texture_, nullptr);
            width_ = rhs.width_;
            height_ = rhs.height_;
        }

        texture& operator=(texture&& rhs) noexcept {
            SDL_DestroyTexture(texture_);
            texture_ = std::exchange(rhs.texture_, nullptr);
            width_ = rhs.width_;
            height_ = rhs.height_;
            return *this;
        }

        ~texture() {
            SDL_DestroyTexture(texture_);
        }

        native_handle_type native_handle() const noexcept {
            return texture_;
        }

        int width() const noexcept {
            return width_;
        }

        int height() const noexcept {
            return height_;
        }
    protected:
        SDL_Texture* texture_;
        int width_;
        int height_;
    };
}

#endif