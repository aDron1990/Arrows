#pragma once

#include "kwee/systems/Application.h"
#include <iostream>
#include <GL/glew.h>

int main()
{
    try
    {
        auto app = kwee::CreateApplication();
        app->run();
        delete app;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}