// NSF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <memory>
#include <iostream>
#include <stdlib.h>

#include "SDL/App.h"
#include "ECS/Components/BallSpawner.h"
#include "ECS/GameObject.h"
#include "World/Scene.h"
#include "World/World.h"
#include "Physics/RigidBody.h"

int main(int argc, char* args[]) {
	NSF::App app;

	int result;
	if ((result = app.Initialize()) != 0) {
		return result;
	}

	NSF::World& world = app.GetWorld();
	NSF::Scene& scene = world.GetScene();

	/*std::shared_ptr<NSF::GameObject> go = scene->CreateGameObject();
	go->Transform()->SetScale(glm::vec2(50, 50));
	go->Transform()->SetPosition(glm::vec2(800, 450));
	std::shared_ptr<NSF::SpriteRenderer> sr = go->AddComponent<NSF::SpriteRenderer>();
	std::shared_ptr<NSF::RigidBody> rb = go->AddComponent<NSF::RigidBody>();

	auto go2 = scene->CreateGameObject();
	go2->Transform()->SetScale(glm::vec2(50, 50));
	go2->Transform()->SetPosition(glm::vec2(825, 350));
	auto sr2 = go2->AddComponent<NSF::SpriteRenderer>();
	auto rb2 = go2->AddComponent<NSF::RigidBody>();*/

	/*for (int i = 0; i < 20; i++) {
		auto& go = scene.CreateGameObject();
		go.Transform().SetScale(glm::vec2(10, 10));
		go.Transform().SetPosition(glm::vec2(650 + (i * 20), 350));
		auto& sr = go.AddComponent<NSF::SpriteRenderer>();
		auto& rb = go.AddComponent<NSF::RigidBody>();
	}*/
	
	auto& go = scene.CreateGameObject();
	go.AddComponent<NSF::BallSpawner>();

	app.Run();

	return 0;
}