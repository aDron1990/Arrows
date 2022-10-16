#include <iostream>

#include "mvc/Model.h"
#include "mvc/View.h"
#include "mvc/Controller.h"

int main()
{
	arrows::mvc::View view{};
	arrows::mvc::controller.init(&view);
	arrows::mvc::model.addListener(&view);

	arrows::mvc::controller.run();

	return 0;
}