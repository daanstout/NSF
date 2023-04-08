#include "RigidBody.h"
#include "Physics.h"
#include "../World/Scene.h"
#include "../ECS/Transform2D.h"
#include "../World/UpdateData.h"

void NSF::RigidBody::Start() {
	lastPosition = GetTransform().GetPosition();
	GetScene()->GetPhysics().RegisterRigidBody(*this);
}

void NSF::RigidBody::Update(float deltaTime) {
	auto& position = GetTransform().GetPosition();
	auto displacement = position - lastPosition;
	lastPosition = position;
	auto newPos = position + displacement + acceleration * deltaTime * deltaTime;
	acceleration = glm::vec2(0, 0);
	GetTransform().SetPosition(newPos);
}

void NSF::RigidBody::End() {
	GetScene()->GetPhysics().UnregisterRigidBody(*this);
}
