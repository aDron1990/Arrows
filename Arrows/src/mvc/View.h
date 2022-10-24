#pragma once

#include "observer/Observer.h"
#include "../systems/Window.h"
#include "event/MEvent.h"
#include "../graphics/Shader.h"

#include <iostream>

namespace arrows::mvc
{
	class View : public observer::Observer<MEvent>
	{
		friend class Controller;

	private:

		systems::Window* window_;

	public:

		View();
		~View();

		void update(MEvent e);

		void draw();

		systems::Window* getWindow();

	};
}