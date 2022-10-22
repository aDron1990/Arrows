#include "App.h"

arrows::mvc::App* arrows::mvc::App::instance_ = nullptr;

arrows::mvc::App::App()
{
	if (instance_ != nullptr) throw;
	instance_ = this;

	view_ = new View;
	model_ = new Model;
	controller_ = new Controller{ view_, model_ };
}

arrows::mvc::App::~App()
{
	delete controller_;
	delete model_;
	delete view_;
}

arrows::mvc::Controller* arrows::mvc::App::getController()
{
	return controller_;
}

arrows::mvc::View* arrows::mvc::App::getView()
{
	return view_;
}

arrows::mvc::App* arrows::mvc::App::getInstance()
{
	return instance_;
}

void arrows::mvc::App::run()
{
	controller_->run();
}