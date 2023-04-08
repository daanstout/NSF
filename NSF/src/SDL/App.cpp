#include "App.h"
#include <iostream>
#include <string>
#include "../World/UpdateData.h"
#include "../World/Time.h"

namespace NSF {
	App::App() : isRunning(false), window(nullptr), renderer(nullptr), world(nullptr) {}

	int App::Initialize() {
		int windowFlags = 0;

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
			return -1;
		}

		window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

		if (!window) {
			std::cout << "Error creating window: " << SDL_GetError() << std::endl;
			return -1;
		}

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

		world = std::make_shared<World>(window);

		isRunning = true;
		return 0;
	}

	void App::Run() {
		Load();

		Uint64 now = SDL_GetPerformanceCounter();
		Uint64 last = 0;
		float deltaTime = 0;

		const float timeBetweenPhysicsUpdates = 1.0f / 60.0f;
		float timeTillNextPhysicsUpdate = -0.00001f;

		const std::shared_ptr<Time> time = std::make_shared<Time>();
		const std::shared_ptr<UpdateData> data = std::make_shared<UpdateData>(time.get());

		while (isRunning) {
			last = now;
			now = SDL_GetPerformanceCounter();

			deltaTime = (float)((now - last) * 1000 / (float)SDL_GetPerformanceFrequency()) * 0.001f;
			time->Update(deltaTime);

			HandleInput();

			if (timeTillNextPhysicsUpdate <= 0.0f) {
				time->FixedUpdate(timeBetweenPhysicsUpdates);
				world->FixedUpdate(*data);
				timeTillNextPhysicsUpdate += timeBetweenPhysicsUpdates;
			} else {
				timeTillNextPhysicsUpdate -= deltaTime;
			}

			world->Update(*data);
			SDL_SetWindowTitle(window, std::to_string(deltaTime).c_str());

			Render();
		}

		CleanUp();
	}

	void App::Load() {}

	void App::HandleInput() {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
				default:
					break;
			}
		}
	}

	void App::Render() {
		world->Render();
	}

	void App::CleanUp() {

	}
}
