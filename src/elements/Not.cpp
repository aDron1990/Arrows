#include "Not.h"

Not::Not(Grid* grid, Direction dir) : Arrow(grid, ArrowType::Not, dir, "not_active", "not_unactive")
{

}

void Not::action()
{
	if (getState())
	{
		sendSignal(getDir().getGridOffset());
		setState(false);
	}
}

void Not::setSignals(int sig)
{
	if (sig == 0) setState(true);
}