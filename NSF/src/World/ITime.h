#pragma once

namespace {
	class ITime {
	public:
		inline const float GetDeltaTime() const { return deltaTime; }
		inline const float GetFixedDeltaTime() const { return fixedDeltaTime; }
		inline const float GetTotalTime() const { return totalTime; }
		inline const float GetDeltaTimeSquared() {
			if (deltaTimeSquared == -1) {
				deltaTimeSquared = deltaTime * deltaTime;
			}

			return deltaTimeSquared;
		}
		inline const float GetInverseDeltaTime() {
			if (inverseDeltaTime == -1) {
				inverseDeltaTime = 1 / deltaTime;
			}

			return inverseDeltaTime;
		}

	protected:
		float deltaTime;
		float fixedDeltaTime;
		float totalTime;
		float deltaTimeSquared;
		float inverseDeltaTime;
	};
}
