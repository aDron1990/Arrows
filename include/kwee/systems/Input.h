#pragma once

#include "kwee/core/api.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace kwee
{
	class Input
	{
	private:

		static bool key[512];
		static bool key_down[512];
		static bool key_up[512];
		static bool m_button[8];
		static bool m_button_down[8];
		static bool m_button_up[8];
		static glm::vec2 m_wheel_scroll;

		static glm::ivec2 mousePos;

	public:

		static void initialize(GLFWwindow* window);
		static void terminate(GLFWwindow* window);

		static void update();

		static void setKey(int code, bool action);
		static bool getKey(int code);
		static bool getKeyUp(int code);
		static bool getKeyDown(int code);

		static void setMouseButton(int code, bool action);
		static bool getMouseButton(int code);
		static bool getMouseButtonUp(int code);
		static bool getMouseButtonDown(int code);

		static void setMousePosition(glm::vec2 pos);
		static glm::vec2 getMousePosition();

		static void setMouseWheelScroll(glm::vec2 scrool);
		static glm::vec2 getMouseWheelScroll();
	};
}