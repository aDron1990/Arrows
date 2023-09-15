#include "And.h"

And::And(Grid* grid, Direction dir) : Arrow(grid, ArrowType::And, dir, "and_active", "and_unactive")
{

}

void And::action()
{
	if (getState())
	{
		sendSignal(getDir().getGridOffset());
		setState(false);
	}
}

void And::setSignals(int sig)
{
	if (sig >= 2) setState(true);
}