#pragma once

#include "Arrow.h"

class TreeWire : public Arrow
{
public:

	TreeWire(Grid* grid, Direction dir);

	void action() override;
	void setSignals(int sig) override;
};