#pragma once

#include "Arrow.h"

class DoubleWire : public Arrow
{
public:

	DoubleWire(Grid* grid, Direction dir);

	void action() override;
	void setSignals(int sig) override;
};

