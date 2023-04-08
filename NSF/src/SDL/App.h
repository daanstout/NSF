#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "Rendering/Texture.h"
#include "../defines.h"
#include "../World/World.h"

namespace NSF {
	class App {
	private:
		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::shared_ptr<World> world;

	public:
		App();

		int Initialize();
		void Run();

		inline World& GetWorld() { return *(world.get()); }

	private:
		void HandleInput();
		void Load();
		void Render();
		void CleanUp();
	};
}
