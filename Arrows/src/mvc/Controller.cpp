#include "Controller.h"
#include "View.h"
#include "../systems/Input.h"

#include <Windows.h>

arrows::mvc::Controller::Controller(View* view, Model* model) : view_(std::move(view)), model_(std::move(model))
{
	running = true;
	systems::input.controller_ = this;
}

arrows::mvc::Controller::~Controller()
{
	systems::input.controller_ = 0;
}

void arrows::mvc::Controller::run()
{
	while (running)
	{
		pollEvents_();

		view_->draw();

		systems::input.update();
	}
}

void arrows::mvc::Controller::pollEvents_()
{
	view_->window_->pollEvents();
}

void arrows::mvc::Controller::sendCommand(CCommand com)
{
	switch (com)
	{
	case arrows::mvc::Controller::CCommand::Close:
		running = false;
		break;
	
	default:
		break;
	}
}