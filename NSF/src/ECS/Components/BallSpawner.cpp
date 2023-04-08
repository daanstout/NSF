#include <stdlib.h>

#include "BallSpawner.h"
#include "../../World/UpdateData.h"
#include "../../World/Scene.h"
#include "../GameObject.h"
#include "SpriteRenderer.h"
#include "../../Physics/RigidBody.h"

void NSF::BallSpawner::Update(const UpdateData& updateData) {
	if (ballsToSpawn <= 0) {
		return;
	}

	timeTillNextSpawn -= updateData.time.GetDeltaTime();

	if (timeTillNextSpawn <= 0.0f) {
		SpawnBall();
		timeTillNextSpawn += timeBetweenSpawns;
		ballsToSpawn--;
	}
}

void NSF::BallSpawner::SpawnBall() {
	auto& go = GetScene()->CreateGameObject();
	go.Transform().SetScale(glm::vec2(10, 10));
	int x = rand() % 100 - 50;
	go.Transform().SetPosition(glm::vec2(ballX + x, ballY));
	go.AddComponent<SpriteRenderer>();
	go.AddComponent<RigidBody>();
}
