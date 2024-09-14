#include "kwee/systems/Input.h"
#include "kwee/systems/Application.h"

#include <memory>
#include <iostream>
#include <cstring>

bool kwee::Input::key[512] = { 0 };
bool kwee::Input::key_up[512] = { 0 };
bool kwee::Input::key_down[512] = { 0 };
bool kwee::Input::m_button[8] = { 0 };
bool kwee::Input::m_button_down[8] = { 0 };
bool kwee::Input::m_button_up[8] = { 0 };
glm::vec2 kwee::Input::m_wheel_scroll = glm::vec2{ 0 };
glm::ivec2 kwee::Input::mousePos = glm::ivec2{0};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_REPEAT)	kwee::Input::setKey(key, action);
}

void mbutton_callback(GLFWwindow* window, int key, int action, int mods)
{
	if (action != GLFW_REPEAT)	kwee::Input::setMouseButton(key, action);
}

void windowclose_callback(GLFWwindow* window)
{
	kwee::Application::getInstance()->onWindowClose();
}

void cursorposition_callback(GLFWwindow* window, double xpos, double ypos)
{
	kwee::Input::setMousePosition({ xpos, ypos });
}

void wheelscroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	kwee::Input::setMouseWheelScroll({ xoffset, yoffset });
}

void kwee::Input::initialize(GLFWwindow* window)
{
	memset(key, 0, sizeof(key));
	memset(key_up, 0, sizeof(key_up));
	memset(key_down, 0, sizeof(key_down));
	memset(m_button, 0, sizeof(m_button));
	memset(m_button_up, 0, sizeof(m_button_up));
	memset(m_button_down, 0, sizeof(m_button_down));
	m_wheel_scroll = glm::vec2(0.0f);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mbutton_callback);
	glfwSetCursorPosCallback(window, cursorposition_callback);
	glfwSetWindowCloseCallback(window, windowclose_callback);
	glfwSetScrollCallback(window, wheelscroll_callback);
}

void kwee::Input::terminate(GLFWwindow* window)
{
	glfwSetKeyCallback(window, 0);
}

void kwee::Input::update()
{
	memset(key_up, 0, sizeof(key_up));
	memset(key_down, 0, sizeof(key_down));
	memset(m_button_up, 0, sizeof(m_button_up));
	memset(m_button_down, 0, sizeof(m_button_down));
	m_wheel_scroll = glm::vec2(0.0f);
}

void kwee::Input::setKey(int code, bool action)
{
	if (action)
	{
		key[code] = true;
		key_down[code] = true;
	}
	else
	{
		key[code] = false;
		key_up[code] = true;
	}
}

void kwee::Input::setMouseButton(int code, bool action)
{
	if (action)
	{
		m_button[code] = true;
		m_button_down[code] = true;
	}
	else
	{
		m_button[code] = false;
		m_button_up[code] = true;
	}
}

bool kwee::Input::getKey(int code)
{
	return key[code];
}

bool kwee::Input::getKeyUp(int code)
{
	return key_up[code];
}

bool kwee::Input::getKeyDown(int code)
{
	return key_down[code];
}

bool kwee::Input::getMouseButton(int code)
{
	return m_button[code];
}

bool kwee::Input::getMouseButtonUp(int code)
{
	return m_button_up[code];
}

bool kwee::Input::getMouseButtonDown(int code)
{
	return m_button_down[code];
}

void kwee::Input::setMousePosition(glm::vec2 pos)
{
	mousePos = pos;
}

glm::vec2 kwee::Input::getMousePosition()
{
	return mousePos;
}

void kwee::Input::setMouseWheelScroll(glm::vec2 scrool)
{
	m_wheel_scroll = scrool;
}

glm::vec2 kwee::Input::getMouseWheelScroll()
{
	return m_wheel_scroll;
}
