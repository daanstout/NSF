#pragma once

#include <memory>
#include <SDL.h>
#include "Scene.h"

namespace NSF {
	struct UpdateData;

	class World {
	private:
		SDL_Window* window;
		std::shared_ptr<Scene> scene;
		int sceneId;

	public:
		World(SDL_Window* window);

		void Update(const UpdateData& updateData);
		void FixedUpdate(const UpdateData& updateData);
		void Render();
		inline Scene& GetScene() { return *(scene.get()); }
	};
}
