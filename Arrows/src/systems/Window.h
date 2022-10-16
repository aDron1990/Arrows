#pragma once

#include <string>

namespace arrows::mvc { class Controller; }
namespace arrows::systems
{
	class Window
	{
		friend class mvc::Controller;

	private:

	public:

		const void* getWindow_();

		Window(std::string name, int width, int height);
		~Window();

		void pollEvents();
		void swapBuffers();

	};
}