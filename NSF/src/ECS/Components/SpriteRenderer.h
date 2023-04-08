#pragma once

#include <memory>
#include "../Component.h"
#include "../../SDL/Rendering/Texture.h"
#include "../Transform2D.h"

namespace NSF {
	class Scene;

	class SpriteRenderer : public Component {
	private:
		std::shared_ptr<Texture> texture;

	public:
		SpriteRenderer() : texture(nullptr) {}

		void Load(SDL_Renderer* renderer) {
			texture = std::make_shared<Texture>(renderer, "C:\\Users\\Daan\\Pictures\\ball.png");
		}

		void Render(SDL_Renderer* renderer) {
			texture->Render(renderer, GetTransform().GetBounds());
		}
	};
}
