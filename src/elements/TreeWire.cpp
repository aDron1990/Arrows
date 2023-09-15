#include "TreeWire.h"

TreeWire::TreeWire(Grid* grid, Direction dir) : Arrow(grid, ArrowType::TreeWire, dir, "treewire_active", "treewire_unactive")
{

}

void TreeWire::action()
{
	if (getState())
	{
		glm::ivec2 offset = getDir().getGridOffset();
		glm::ivec2 side_offset;
		sendSignal(offset);
		if (offset.x == 0)	side_offset = { 1, 0 };
		else				side_offset = { 0, 1 };
		sendSignal(side_offset);
		sendSignal(-side_offset);

		setState(false);
	}
}

void TreeWire::setSignals(int sig)
{
	if (sig) setState(true);
}