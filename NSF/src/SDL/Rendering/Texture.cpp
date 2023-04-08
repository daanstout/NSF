#include "Texture.h"

namespace NSF {
	Texture::Texture(SDL_Renderer* renderer, const char* path) {
		texture = IMG_LoadTexture(renderer, path);
	}

	void Texture::Render(SDL_Renderer* renderer, const SDL_FRect& position) const {
		int width = (int)position.w;
		int height = (int)position.h;
		SDL_QueryTexture(texture, 0, 0, &width, &height);

		SDL_RenderCopyF(renderer, texture, nullptr, &position);
	}
}
