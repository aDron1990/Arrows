#pragma once

#include "Arrow.h"

class Not : public Arrow
{
public:

	Not(Grid* grid, Direction dir);

	void action() override;
	void setSignals(int sig) override;
};