#pragma once

#include "Arrow.h"

class Lever : public Arrow
{

private:

	bool lever_state = false;
	std::shared_ptr<kwee::Texture> unactive;
	std::shared_ptr<kwee::Texture> active;

public:

	Lever(Grid* grid, Direction dir);

	void action() override;
	void setSignals(int sig) override;
	void onClick() override;
};

