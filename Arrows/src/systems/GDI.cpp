#include "Renderer.h"
#include "../mvc/App.h"

#include <Windows.h>

HWND window_;
HDC dc;

void arrows::systems::Renderer::initGDIRenderer(Window* window)
{
    window_ = window->getWindow_();

    dc = GetDC(window_);
}