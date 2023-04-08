#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_render.h>
#include "Object.h"

namespace NSF {
	class GameObject;
	class Transform2D;
	class Scene;
	struct UpdateData;

	class Component : public Object {
		friend Scene;
	private:
		int parent;
		Scene* scene;
		GameObject* gameObject;
		bool firstUpdate;

	public:
		Component() : parent(-1), scene(nullptr), gameObject(nullptr), firstUpdate(true) {}

		inline int GetParent() const { return parent; }

		GameObject& GetCameObject();
		Transform2D& GetTransform();

		void TryStart();
		void Destroy();

		virtual void Load(SDL_Renderer* renderer) {}
		virtual void Start() {}
		virtual void FixedUpdate(const UpdateData& updateData) {}
		virtual void Update(const UpdateData& updateData) {}
		virtual void End() {}
		virtual void Render(SDL_Renderer* renderer) {}
		virtual void Load() {}

	protected:
		Scene* GetScene() { return scene; }

	private:
		inline void SetData(Scene* scene, const int parent) {
			this->scene = scene;
			this->parent = parent;
		}
	};
}
