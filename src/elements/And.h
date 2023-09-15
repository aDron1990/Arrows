#pragma once

#include "Arrow.h"

class And : public Arrow
{
public:

	And(Grid* grid, Direction dir);

	void action() override;
	void setSignals(int sig) override;
};