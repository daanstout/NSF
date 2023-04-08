#pragma once

#include <glm.hpp>
#include <vector>
#include <memory>
#include "../RigidBody.h"
#include "../../ECS/Transform2D.h"

namespace NSF {
	template <size_t TWidth, size_t THeight>
	class FixedGrid {
	private:
		const int cellWidth;
		const int cellHeight;
		const int width;
		const int height;
		const glm::vec2 offset;
		std::vector<RigidBody*> cells[TWidth][THeight];

	public:
		FixedGrid(int cellWidth, int cellHeight, glm::vec2 offset) : cellWidth(cellWidth),
			cellHeight(cellHeight),
			width(TWidth),
			height(THeight),
			offset(offset) {
			/*for (size_t w = 0; w < TWidth; w++) {
				for (size_t h = 0; h < THeight; h++) {
					cells[w, h] = std::vector<RigidBody*>;
				}
			}*/
		}

		std::vector<RigidBody*>& GetBodiesNearBody(RigidBody& body) {
			glm::vec2 currentCell = body.GetCellPosition();

			float startX = currentCell.x > 0 ? currentCell.x - 1 : currentCell.x;
			float endX = currentCell.x < width - 1 ? currentCell.x + 1 : currentCell.x;

			float startY = currentCell.y > 0 ? currentCell.y - 1 : currentCell.y;
			float endY = currentCell.y < height - 1 ? currentCell.y + 1 : currentCell.y;

			std::vector<RigidBody*>* result = new std::vector<RigidBody*>();

			for (int x = (int)startX; x <= endX; x++) {
				for (int y = (int)startY; y <= endY; y++) {
					for (RigidBody* otherBody : cells[x][y]) {
						if (otherBody->GetID() != body.GetID()) {
							result->push_back(otherBody);
						}
					}
				}
			}

			return *result;
		}

		void UpdateBodyCell(RigidBody& body) {
			int cellX, cellY;
			CalculateCellPosition(body, cellX, cellY);

			if (cellX == body.GetCellPosition().x && cellY == body.GetCellPosition().y) {
				return;
			}

			RemoveBody(body);
			AddBody(body);
		}

		void AddBody(RigidBody& body) {
			int cellX, cellY;
			CalculateCellPosition(body, cellX, cellY);
			AddBody(body, glm::ivec2(cellX, cellY));
		}

		void RemoveBody(RigidBody& body) {
			std::vector<RigidBody*> listToRemoveFrom = cells[(size_t)body.GetCellPosition().x][(size_t)body.GetCellPosition().y];
			listToRemoveFrom.erase(std::remove_if(listToRemoveFrom.begin(),
				listToRemoveFrom.end(),
				[body](RigidBody* otherBody) {
				return body.GetID() == otherBody->GetID();
			}), listToRemoveFrom.end());
		}

	private:
		void CalculateCellPosition(RigidBody& body, int& cellX, int& cellY) {
			glm::vec2 pos = body.GetTransform().GetPosition();
			cellX = (int)(pos.x - offset.x);
			cellY = (int)(pos.y - offset.y);

			cellX /= cellWidth;
			cellY /= cellHeight;
		}

		void AddBody(RigidBody& body, const glm::ivec2& cell) {
			cells[(size_t)cell.x][(size_t)cell.y].push_back(&body);
			body.SetCellPosition(cell);
		}
	};
}
