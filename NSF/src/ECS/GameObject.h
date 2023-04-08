#pragma once

#include <memory>
#include "Transform2D.h"
#include "Object.h"
#include "Utils.h"
#include "../World/Scene.h"

namespace NSF {
	class GameObject : public Object {
	private:
		std::shared_ptr<Transform2D> transform;
		Scene* scene;

	public:
		GameObject(Scene& scene) : scene(&scene), transform(std::make_shared<Transform2D>()) {}

		inline Transform2D& Transform() const { return *(transform.get()); }

		template<IsComponent T>
		inline T& AddComponent() { return scene->CreateComponent<T>(id); }
		template<IsComponent T>
		inline T& GetComponent() const { return scene->GetComponent<T>(id); }

		inline void Destroy() { scene->DestroyGameObject(id); }
	};
}
