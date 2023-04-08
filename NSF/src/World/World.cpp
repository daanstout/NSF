#include "World.h"
#include <iostream>

NSF::World::World(SDL_Window* window) : window(window), scene(nullptr), sceneId(0) {
	auto* renderer = SDL_CreateRenderer(window, sceneId++, SDL_RENDERER_ACCELERATED);
	
	if (!renderer) {
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return;
	}
	
	scene = std::make_shared<Scene>(*renderer);
}

void NSF::World::Update(const UpdateData& updateData) {
	scene->Update(updateData);
}

void NSF::World::FixedUpdate(const UpdateData& updateData) {
	scene->FixedUpdate(updateData);
}

void NSF::World::Render() {
	scene->Render();
}
