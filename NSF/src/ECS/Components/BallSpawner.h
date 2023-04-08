#pragma once

#include <memory>
#include "../Component.h"
#include "../../SDL/Rendering/Texture.h"
#include "../Transform2D.h"

namespace NSF {
	class BallSpawner : public Component {
	private:
		int ballsToSpawn = 100;
		int ballX = 800;
		int ballY = 350;
		float timeTillNextSpawn = 0.0f;
		const float timeBetweenSpawns = 0.25f;

	public:
		void Update(const UpdateData& updateData);

	private:
		void SpawnBall();
	};
}