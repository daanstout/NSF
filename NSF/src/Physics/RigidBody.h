#pragma once

#include <memory>
#include <glm.hpp>
#include <memory>
#include "../ECS/Component.h"

namespace NSF {
	class RigidBody : public Component {
	private:
		glm::vec2 velocity;
		glm::vec2 acceleration;
		float restitution = 1;
		float mass = 1;
		glm::vec2 lastPosition;
		glm::ivec2 cellPosition;

	public:
		void Start();
		void Update(float deltaTime);
		void End();

		inline const glm::ivec2& GetCellPosition() const { return cellPosition; }
		inline void SetCellPosition(const glm::ivec2 position) 
		{ 
			cellPosition.x = position.x; 
			cellPosition.y = position.y;
		}
		inline void AddAcceleration(const glm::vec2 acceleration) { this->acceleration += acceleration; }
		inline const float GetMass() const { return mass; }
		inline void SetMass(const float mass) { this->mass = mass; }
	};
}

