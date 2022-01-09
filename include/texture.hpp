#ifndef SDLGAME_TEXTURE_HPP
#define SDLGAME_TEXTURE_HPP

#include <algorithm>

#include <SDL2/SDL.h>

namespace sdlgame {
    class texture final {
    public:
        using native_handle_type = SDL_Texture*;

        texture() noexcept : texture_(nullptr) {}

        explicit texture(SDL_Texture* tex) noexcept : texture_(tex) {}

        texture(texture&& rhs) noexcept {
            texture_ = std::exchange(rhs.texture_, nullptr);
        }

        texture& operator=(texture&& rhs) noexcept {
            SDL_DestroyTexture(texture_);
            texture_ = std::exchange(rhs.texture_, nullptr);
            return *this;
        }

        ~texture() {
            SDL_DestroyTexture(texture_);
        }

        native_handle_type native_handle() const noexcept {
            return texture_;
        }
    protected:
        SDL_Texture* texture_;
    };
}

#endif