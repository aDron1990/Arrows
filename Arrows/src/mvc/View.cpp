#include "View.h"
#include "../systems/Renderer.h"

#include <Windows.h>

arrows::mvc::View::View()
{
	window_ = new systems::Window("Arrows", 800, 600);
	systems::renderer.init();
}

arrows::mvc::View::~View()
{
	systems::renderer.term();
	delete window_;
}


void arrows::mvc::View::update(arrows::mvc::MEvent e)
{
	
}

void arrows::mvc::View::draw()
{
}
