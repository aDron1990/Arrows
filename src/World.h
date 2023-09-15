#pragma once

#include "Grid.h"
#include "ArrowUIButton.h"

#include <kwee/kwee.h>
#include <array>

class World : public kwee::Scene
{
private:

	kwee::GameObject* test;

public:

	std::vector<ArrowUIButton*> buttons;

	kwee::Camera* arrowPanelView;
	Grid* grid;
	kwee::GameObject* phantomArrow;

	void onDraw() override;

	World();
	~World();

};

