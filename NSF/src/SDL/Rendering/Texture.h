#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_image.h>

namespace NSF {
	class Texture {
	private:
		SDL_Texture* texture;

	public:
		Texture(SDL_Renderer* renderer, const char* path);

		void Render(SDL_Renderer* renderer, const SDL_FRect& position) const;
	};
}
