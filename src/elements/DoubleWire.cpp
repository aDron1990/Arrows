#include "DoubleWire.h"

DoubleWire::DoubleWire(Grid* grid, Direction dir) : Arrow(grid, ArrowType::DoubleWire, dir, "doublewire_active", "doublewire_unactive")
{

}

void DoubleWire::action()
{
	if (getState())
	{
		sendSignal(getDir().getGridOffset() * 2);
		setState(false);
	}
}

void DoubleWire::setSignals(int sig)
{
	if (sig > 0) setState(true);
}