#pragma once

#include "elements/Arrow.h"
#include "elements/Wire.h"
#include "elements/DoubleWire.h"
#include "elements/Block.h"
#include "elements/Not.h"
#include "elements/And.h"
#include "elements/TreeWire.h"
#include "elements/Lever.h"

#include <kwee/kwee.h>

class Grid : public kwee::GameObject
{
	friend class Arrows;

private:

	glm::vec2 size_;
	Direction dir_;
	bool hover = false;

public:

	ArrowType at = ArrowType::Wire;

	Arrow*** arrows;
	int** signals;

	void sendSignal(glm::ivec2 source, glm::ivec2 offset);
	void simulate();

	Grid(int size);
	~Grid();

	void update() override;
	void clear();

	void onMouseHover() override;
	void onMouseHoverEnter() override;
	void onMouseHoverExit() override;

	glm::ivec2 WorldToGrid(glm::vec2 worldCoords);
	glm::vec2 GridToWorld(glm::vec2 gridCoords);
	Arrow* createArrow(Grid* grid, ArrowType at, Direction dir);

	glm::vec2 getSize();
};

