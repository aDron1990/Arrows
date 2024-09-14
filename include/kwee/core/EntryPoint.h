#pragma once

#ifndef ENTRY
#define ENTRY
#include "kwee/systems/Application.h"

int main()
{
	auto app = kwee::CreateApplication();
	app->run();
	delete app;
}

#endif // !ENTRY