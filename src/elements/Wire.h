#pragma once

#include "Arrow.h"

class Wire : public Arrow
{
public:

	Wire(Grid* grid, Direction dir);

	void action() override;
	void setSignals(int sig) override;
};

