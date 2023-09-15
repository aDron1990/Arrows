#include "Lever.h"

Lever::Lever(Grid* grid, Direction dir) : Arrow(grid, ArrowType::Lever, dir, "lever_unactive", "lever_unactive")
{
	active = kwee::ResourceManager::getTexture("lever_active");
	unactive = kwee::ResourceManager::getTexture("lever_unactive");
}

void Lever::action()
{
	if (getState() && lever_state)
	{
		sendSignal(getDir().getGridOffset());
		
	}
	setState(false);
	if (lever_state)
		setTexture(active);
	else
		setTexture(unactive);
}

void Lever::setSignals(int sig)
{
	if (sig > 0)
	{
		setState(true);
		if (lever_state)
			setTexture(active);
		else
			setTexture(unactive);
	}

}

void Lever::onClick()
{
	lever_state = !lever_state;
	if (lever_state)
	{
		setTexture(active);
	}
	else
	{
		setTexture(unactive);
	}
}