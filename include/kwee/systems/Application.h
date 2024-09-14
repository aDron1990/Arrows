#pragma once

#include "kwee/core/api.h"
#include "Input.h"
#include "kwee/game_primitives/Scene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace kwee
{
	class KWEEAPI Application
	{
	private:

		static Application* instance_;
		static bool running_;
		Scene* activeScene_;
		glm::vec2 windowSize_;

	protected:

		GLFWwindow* window;

	public:

		GLuint vbo_, vao_, ebo_;

		Application(glm::vec2 windowSize, std::string windowName, bool allocConsole);
		virtual ~Application();
		static Application* getInstance();

		void run();
		void loadScene(Scene* scene);
		void render();

		virtual void drawUI() {};
		virtual void update() {};
		virtual void onWindowClose() {};

		Scene* getScene();
		glm::vec2 getWindowSize();
		static void close();
	};

	extern kwee::Application* CreateApplication();
}