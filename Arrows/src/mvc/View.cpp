#include "View.h"
#include "../systems/Renderer.h"

#include <Windows.h>

arrows::mvc::View::View()
{
	window_ = new systems::Window("Arrows", 800, 600);
	systems::renderer.init(window_->getViewportSize());	
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
	systems::renderer.draw();
	window_->swapBuffers();
}

arrows::systems::Window* arrows::mvc::View::getWindow()
{
	return window_;
}
