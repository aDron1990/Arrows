#include "Block.h"

Block::Block(Grid* grid, Direction dir) : Arrow(grid, ArrowType::Block, dir, "block_active", "block_active")
{

}

void Block::action()
{
	if (getState())
	{
		sendSignal({  1,  0 });
		sendSignal({ -1,  0 });
		sendSignal({  0,  1 });
		sendSignal({  0, -1 });
		setState(false);
	}
}

void Block::setSignals(int sig)
{
	setState(true);
}