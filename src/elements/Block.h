#pragma once

#include "Arrow.h"

class Block : public Arrow
{
public:

	Block(Grid* grid, Direction dir);

	void action() override;
	void setSignals(int sig) override;
};

