#include "Component.h"
#include "../World/Scene.h"
#include "GameObject.h"

namespace NSF {
	GameObject& Component::GetCameObject() {
		if (gameObject == nullptr) {
			gameObject = scene->GetGameObject(parent);
		}

		return *gameObject;
	}

	Transform2D& Component::GetTransform() {
		return GetCameObject().Transform();
	}
	
	void Component::TryStart() {
		if (firstUpdate) {
			Start();
			firstUpdate = false;
		}
	}

	void Component::Destroy() {
		scene->DestroyComponent(id);
	}
}
