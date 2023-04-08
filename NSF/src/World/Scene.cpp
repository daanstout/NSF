#include "Scene.h"
#include "../ECS/GameObject.h"
#include "../ECS/Component.h"
#include "../Physics/Physics.h"

namespace NSF {
	Scene::Scene(SDL_Renderer& renderer) : renderer(&renderer), physics(std::make_shared<Physics>()) {}

	GameObject& Scene::CreateGameObject() {
		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(*this);

		gameObjects.push_back(std::move(gameObject));

		return *(gameObjects.back().get());
	}

	void Scene::Update(const UpdateData& updateData) {
		//for (auto& component : components) {
		for (int i = 0; i < components.size(); i++) {
			auto* component = components[i].get();
			component->TryStart();
			component->Update(updateData);
		}
	}

	void Scene::FixedUpdate(const UpdateData& updateData) {
		physics->Step(updateData);
		for (auto& component : components) {
			component->TryStart();
			component->FixedUpdate(updateData);
		}
	}

	void Scene::Render() {
		SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
		SDL_RenderClear(renderer);

		for (auto& component : components) {
			component->Render(renderer);
		}

		SDL_RenderPresent(renderer);
	}

	GameObject* Scene::GetGameObject(const int id) {
		for (auto& gameObject : gameObjects) {
			if (gameObject->GetID() == id) {
				return gameObject.get();
			}
		}

		return nullptr;
	}

	void Scene::DestroyGameObject(const int id) {
		for (auto iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
			if (iterator._Ptr->get()->GetID() == id) {
				gameObjects.erase(iterator);
				DestroyComponents(id);
				return;
			}
		}
	}

	void Scene::DestroyComponent(const int id) {
		for (auto iterator = components.begin(); iterator != components.end(); iterator++) {
			if (iterator._Ptr->get()->GetID() == id) {
				((*iterator._Ptr)->End());
				iterator._Ptr->get()->End();
				components.erase(iterator);
				return;
			}
		}
	}

	void Scene::DestroyComponents(const int parent) {
		std::vector<Component*> componentsToRemove;

		componentsToRemove.erase(std::remove_if(componentsToRemove.begin(),
			componentsToRemove.end(),
			[parent](Component* component) {
			if (component->GetParent() == parent) {
				component->End();
				return true;
			}
			return false;
		}));
	}
}