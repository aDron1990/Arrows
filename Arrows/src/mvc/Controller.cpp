#include "Controller.h"
#include "View.h"
#include "../systems/Input.h"

#include <Windows.h>

void arrows::mvc::Controller::init(View* view)
{
	view_ = view;
	running = true;
	systems::input.controller_ = this;
}

void arrows::mvc::Controller::term()
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