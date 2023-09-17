#include "World.h"
#include "main.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>

World::World()
{
	background = { 0.37, 0.63, 0.76 };
	mainCamera = new kwee::Camera(glm::vec4(0, 0, kwee::Application::getInstance()->getWindowSize()));
	mainCamera->setScale(glm::vec2(0.1f, 0.1f));

	glm::vec2 windowSize = kwee::Application::getInstance()->getWindowSize();
	glm::vec4 arrowPanelViewport{ 0, 0, 350, 50 };
	arrowPanelView = new kwee::Camera(arrowPanelViewport);
	arrowPanelView->setScale(glm::vec2(2.0f, 2.0f));

	grid = new Grid{ 250 };
	addObject(grid);

	phantomArrow = new kwee::GameObject("wire_active");
	phantomArrow->alpha = 0.0;
	phantomArrow->mix = 0.2;
	phantomArrow->color = {1.0, 1.0, 1.0};
	phantomArrow->visible = true;
	addObject(phantomArrow);

	for (int i = 0; i < 7; i++)
	{
		buttons.push_back(new ArrowUIButton{ (ArrowType)((int)ArrowType::Wire+i) });
		buttons[i]->setPosition(glm::vec2{i - 3, 0});
	}

	test = new kwee::GameObject{ kwee::Color{0, 0, 0} };
	test->alpha = 0.3;
	test->setScale({7, 1});
}

World::~World()
{
	delete grid;
	delete phantomArrow;
	delete mainCamera;
	delete arrowPanelView;
	delete test;
	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
}

void World::onDraw()
{
	arrowPanelView->useViewport();

	glm::mat4 viewMatrix = arrowPanelView->getViewMatrix();
	glm::mat4 projectionMatrix = arrowPanelView->getProjectionMatrix();
	
	test->draw(viewMatrix, projectionMatrix);

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->draw(viewMatrix, projectionMatrix);
	}
}