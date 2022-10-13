#pragma once

#include "observer/Subject.h"

#include <iostream>


namespace arrows::mvc
{
	class View : public observer::Observer
	{
	public:

		void onUpdate() override
		{

		}
	};
}