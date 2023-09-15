#include "Wire.h"

Wire::Wire(Grid* grid, Direction dir) : Arrow(grid, ArrowType::Wire, dir, "wire_active", "wire_unactive")
{

}

void Wire::action()
{
	if (getState())
	{
		sendSignal(getDir().getGridOffset());
		setState(false);
	}
}

void Wire::setSignals(int sig)
{
	if (sig > 0) setState(true);
}