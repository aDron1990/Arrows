#pragma once

#include "Input.h"
#include "kwee/game_primitives/Scene.h"
#include "kwee/systems/ResourceManagerBase.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <memory>

namespace kwee
{
    class Application
    {

    public:
        Application(glm::vec2 windowSize, std::string windowName, bool allocConsole);
        virtual ~Application();
        static Application* getInstance();
        void run();
        void loadScene(Scene* scene);
        void render();
        virtual void drawUI(){};
        virtual void update(){};
        virtual void onWindowClose(){};
		ResourceManager& getResourceManager();

    public:
        Scene* getScene();
        glm::vec2 getWindowSize();
        static void close();

    protected:
        GLFWwindow* window;

    private:
        static Application* instance_;
        static bool running_;
        Scene* activeScene_;
        glm::vec2 windowSize_;
		ResourceManagerBase resourseManager_;
    };

    extern kwee::Application* CreateApplication();
}