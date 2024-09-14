#include "kwee/systems/Application.h"
#include "kwee/systems/PhysicEngine.h"

#include <iostream>

kwee::Application* kwee::Application::instance_ = 0;
bool kwee::Application::running_ = false;

void framebuffersize_callback(GLFWwindow* window, int width, int height);

kwee::Application::Application(glm::vec2 windowSize, std::string windowName, bool allocConsole) : windowSize_(windowSize)
{
    running_ = true;
    instance_ = this;
    if (glfwInit() == 0) throw;

    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

    window = glfwCreateWindow(windowSize_.x, windowSize_.y, windowName.c_str(), nullptr, nullptr);
    if (window == 0) throw;
    glfwMakeContextCurrent(window);

    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) throw;

    glfwSetFramebufferSizeCallback(window, framebuffersize_callback);

    activeScene_ = 0;
    Input::initialize(window);
    PhysicEngine::initialize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.IniFilename = NULL;
    io.LogFilename = NULL;

    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

kwee::ResourceManager& kwee::Application::getResourceManager()
{
	return resourseManager_;
}

kwee::Application::~Application()
{
    Input::terminate(window);
    glfwDestroyWindow(window);
    glfwTerminate();
}

kwee::Application* kwee::Application::getInstance()
{
    return instance_;
}

void kwee::Application::run()
{
    while (running_)
    {
        glfwPollEvents();

        if (activeScene_ != 0) activeScene_->update();

        PhysicEngine::removeRequiedObjects();
        PhysicEngine::update();

        update();
        render();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        drawUI();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glFlush();

        Input::update();
    }
}

void kwee::Application::loadScene(Scene* scene)
{
    activeScene_ = scene;
}

void kwee::Application::render()
{
    if (activeScene_ != 0)
        activeScene_->draw();
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, 0, 0, 1.0);
    }
}

kwee::Scene* kwee::Application::getScene()
{
    return activeScene_;
}

glm::vec2 kwee::Application::getWindowSize()
{
    return windowSize_;
}

void kwee::Application::close()
{
    running_ = false;
}

void framebuffersize_callback(GLFWwindow* window, int width, int height)
{
    kwee::Application::getInstance()->getScene()->mainCamera->setVieport({0, 0, width, height});
}