#pragma once

#include <string>
#include <glm/glm.hpp>

namespace arrows::mvc { class Controller; }
namespace arrows::systems
{
	class Window
	{
		friend class mvc::Controller;

	private:

	public:

		Window(std::string name, int width, int height);
		~Window();

		void pollEvents();
		void swapBuffers();

		glm::vec2 getViewportSize();
	};
}