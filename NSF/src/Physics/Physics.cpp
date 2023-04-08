#include "Physics.h"
#include "../World/UpdateData.h"

namespace {
	std::vector<NSF::RigidBody*> __neighbours;
}

void NSF::Physics::CheckCollision() {
	const float responseCoefficient = 0.75f;

	for (RigidBody* body : rigidBodies) {
		/*__neighbours.clear();
		fixedGrid.GetBodiesNearBody(*body, __neighbours);
		for (RigidBody* neighbour : __neighbours) {
			auto distanceVec = body->GetTransform().GetPosition() - neighbour->GetTransform().GetPosition();
			auto distance = distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y;
			auto minimumDistance = body->GetTransform().GetHalfScale().x + neighbour->GetTransform().GetHalfScale().x;

			if (distance < minimumDistance * minimumDistance) {
				auto distanceSqrt = sqrtf(distance);
				auto overlap = distanceVec / distanceSqrt;
				auto currentMassRatio = body->GetMass() / (body->GetMass() + neighbour->GetMass());
				auto neighbourMassRatio = 1 - currentMassRatio;
				auto dt = 0.5f * responseCoefficient * (distanceSqrt - minimumDistance);

				body->GetTransform().Move(-overlap * currentMassRatio * dt);
				neighbour->GetTransform().Move(overlap * neighbourMassRatio * dt);
			}
		}*/
		fixedGrid.ForBodiesNearBody(*body, [body, responseCoefficient](RigidBody* neighbour) {
			auto distanceVec = body->GetTransform().GetPosition() - neighbour->GetTransform().GetPosition();
			auto distance = distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y;
			auto minimumDistance = body->GetTransform().GetHalfScale().x + neighbour->GetTransform().GetHalfScale().x;

			if (distance < minimumDistance * minimumDistance) {
				auto distanceSqrt = sqrtf(distance);
				auto overlap = distanceVec / distanceSqrt;
				auto currentMassRatio = body->GetMass() / (body->GetMass() + neighbour->GetMass());
				auto neighbourMassRatio = 1 - currentMassRatio;
				auto dt = 0.5f * responseCoefficient * (distanceSqrt - minimumDistance);

				body->GetTransform().Move(-overlap * currentMassRatio * dt);
				neighbour->GetTransform().Move(overlap * neighbourMassRatio * dt);
			}
		});
	}
}

void NSF::Physics::ApplyConstraint() {
	for (RigidBody* body : rigidBodies) {
		auto offset = constraintCenter - body->GetTransform().GetPosition();
		auto distance = sqrt(offset.x * offset.x + offset.y * offset.y);

		if (distance > constraintRadius - body->GetTransform().GetHalfScale().x) {
			auto toMove = offset / distance;
			body->GetTransform().SetPosition(constraintCenter - toMove * (constraintRadius - body->GetTransform().GetHalfScale().x));
		}
	}
}

void NSF::Physics::UpdateObjects(float deltaTime) {
	for (RigidBody* body : rigidBodies) {
		body->Update(deltaTime);
		fixedGrid.UpdateBodyCell(*body);
	}
}

void NSF::Physics::Step(const UpdateData& data) {
	const float stepTime = data.time.GetFixedDeltaTime() / stepsPerUpdate;

	for (size_t i = 0; i < stepsPerUpdate; i++) {
		ApplyGravity();
		CheckCollision();
		ApplyConstraint();
		UpdateObjects(stepTime);
	}
}

void NSF::Physics::ApplyGravity() {
	for (RigidBody* body : rigidBodies) {
		body->AddAcceleration(gravity);
	}
}
