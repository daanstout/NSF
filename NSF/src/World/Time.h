#pragma once

#include "ITime.h"

namespace NSF {
	class Time : public ITime {
	public:
		inline void Update(const float deltaTime) {
			if (this->deltaTime != deltaTime) {
				deltaTimeSquared = -1;
				inverseDeltaTime = -1;
			}
			this->deltaTime = deltaTime; 
			totalTime += deltaTime;
		}

		inline void FixedUpdate(const float deltaTime) { fixedDeltaTime = deltaTime; }
	};
}
