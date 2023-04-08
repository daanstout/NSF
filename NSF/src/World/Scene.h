#pragma once

#include <SDL.h>
#include <vector>
#include <memory>
#include "../ECS/Utils.h"
#include "../ECS/Component.h"

namespace NSF {
	class GameObject;
	struct UpdateData;
	class Physics;

	class Scene {
	private:
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Component>> components;
		std::shared_ptr<Physics> physics;
		SDL_Renderer* renderer;

	public:
		Scene(SDL_Renderer& renderer);

		GameObject& CreateGameObject();
		void Update(const UpdateData& updateData);
		void FixedUpdate(const UpdateData& updateData);
		void Render();
		template <IsComponent T>
		T& CreateComponent(const int parent) {
			std::shared_ptr<T> component = std::make_shared<T>();

			component->Load(renderer);
			component->SetData(this, parent);

			auto* result = (component.get());

			components.push_back(std::move(component));

			return *result;
		}
		template <IsComponent T>
		T* GetComponent(const int parent) const {
			for (size_t i = 0; i < components.size(); i++) {
				if (components[i]->GetParent() == parent && dynamic_cast<T*>(components[i].get()) != nullptr) {
					return dynamic_cast<T*>(components[i].get());
				}
			}

			return nullptr;
		}
		GameObject* GetGameObject(const int id);
		void DestroyGameObject(const int id);
		void DestroyComponent(const int id);
		inline Physics& GetPhysics() { return *(physics.get()); }

	private:
		void DestroyComponents(const int parent);
	};
}
