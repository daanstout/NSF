#pragma once

#include <vector>
#include <memory>
#include <glm.hpp>
#include "RigidBody.h"
#include "SpatialPartitioning/FixedGrid.h"

namespace NSF {
	class Physics {
	private:
		std::vector<RigidBody*> rigidBodies;
		FixedGrid<32, 18> fixedGrid;

		const int stepsPerUpdate = 8;
		glm::vec2 gravity;
		glm::vec2 constraintCenter;
		float constraintRadius = 200;

	public:
		Physics() : fixedGrid(50, 50, glm::vec2(0.0f, 0.0f)), gravity(0.0f, 100.0f), constraintCenter(800, 450) {}

		inline void RegisterRigidBody(RigidBody& rigidBody) {
			rigidBodies.push_back(&rigidBody);
			fixedGrid.AddBody(rigidBody);
		}
		inline void UnregisterRigidBody(RigidBody& rigidBody) {
			//rigidBodies.erase(std::remove_if(rigidBodies.begin(), rigidBodies.end(), [rigidBody](RigidBody* otherBody) {
			//	return rigidBody.GetID() == otherBody->GetID();
			//}), rigidBodies.end());
			rigidBodies.erase(std::find(rigidBodies.begin(), rigidBodies.end(), &rigidBody));

			fixedGrid.RemoveBody(rigidBody);
		}
		void Step(const UpdateData& data);
		void ApplyGravity();
		void CheckCollision();
		void ApplyConstraint();
		void UpdateObjects(const float deltaTime);
	};
}
