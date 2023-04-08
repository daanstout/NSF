#pragma once

#include <memory>
#include <glm.hpp>
#include <SDL.h>

namespace NSF {
	class Transform2D {
	private:
		glm::vec2 position;
		glm::vec2 scale;
		glm::vec2 halfScale;
		float rotation;
		std::shared_ptr<SDL_FRect> bounds;
		bool dirty;

	public:
		Transform2D() : position(glm::vec2(0.0f, 0.0f)),
			scale(glm::vec2(1.0f, 1.0f)),
			halfScale(glm::vec2(0.5f, 0.5f)),
			rotation(0.0f),
			bounds(std::make_shared<SDL_FRect>()),
			dirty(true) {}

		inline const glm::vec2& GetPosition() const { return position; }
		inline const glm::vec2& GetScale() const { return scale; }
		inline const float GetRotation() const { return rotation; }
		inline const glm::vec2& GetHalfScale() {
			Recalculate();
			return halfScale;
		}
		inline const SDL_FRect& GetBounds() {
			Recalculate();
			return *(bounds.get());
		}

		inline void SetPosition(const glm::vec2& position) {
			this->position = position;
			dirty = true;
		}
		inline void SetScale(const glm::vec2& scale) {
			this->scale = scale;
			dirty = true;
		}
		inline void SetRotation(const float rotation) {
			this->rotation = rotation;
			dirty = true;
		}
		inline void Move(const glm::vec2& movement) {
			position += movement;
			dirty = true;
		}

	private:
		inline void Recalculate() {
			if (dirty) {
				halfScale = scale / 2.0f;
				bounds->x = position.x;
				bounds->y = position.y;
				bounds->w = scale.x;
				bounds->h = scale.y;
				dirty = false;
			}
		}
	};
}
