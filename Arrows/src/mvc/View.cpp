#include "View.h"
#include "../systems/Renderer.h"

#include <Windows.h>
#include <fstream>
#include <sstream>

arrows::mvc::View::View()
{
	window_ = new systems::Window("Arrows", 800, 600);
	systems::renderer.init(window_->getViewportSize());

	std::ifstream vertFile;
	std::ifstream fragFile;
	vertFile.open("main.vert", std::ios::binary);
	fragFile.open("main.frag", std::ios::binary);
	std::stringstream fragSS, vertSS;

	vertSS << vertFile.rdbuf();
	fragSS << fragFile.rdbuf();

	fragFile.close();
	vertFile.close();

	shader.load_(vertSS.str(), fragSS.str());
	shader.use();
}

arrows::mvc::View::~View()
{
	shader.free_();
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
