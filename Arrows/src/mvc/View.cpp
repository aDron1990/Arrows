#include "View.h"

#include <Windows.h>

arrows::mvc::View::View()
{
	window_ = new systems::Window("Arrows", 800, 600);
}

arrows::mvc::View::~View()
{
	delete window_;
}


void arrows::mvc::View::update(arrows::mvc::MEvent e)
{
	
}

void arrows::mvc::View::draw()
{
}
