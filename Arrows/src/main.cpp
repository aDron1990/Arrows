#include <iostream>

#include "mvc/App.h"

int main()
{
	auto app = arrows::mvc::App{};
	app.run();
	return 0;
}