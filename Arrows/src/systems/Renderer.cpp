#include "Renderer.h"
#include "../graphics/Drawable.h"

#include <Windows.h>

static HDC dc;

void arrows::systems::Renderer::init()
{
    int bits = 16;
    PIXELFORMATDESCRIPTOR pfd =              // pfd Tells Windows How We Want Things To Be
    {
        sizeof(PIXELFORMATDESCRIPTOR),              // Size Of This Pixel Format Descriptor
        1,                                          // Version Number
        PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
        PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
        PFD_DOUBLEBUFFER,                           // Must Support Double Buffering
        PFD_TYPE_RGBA,                              // Request An RGBA Format
        bits,                                       // Select Our Color Depth
        0, 0, 0, 0, 0, 0,                           // Color Bits Ignored
        0,                                          // No Alpha Buffer
        0,                                          // Shift Bit Ignored
        0,                                          // No Accumulation Buffer
        0, 0, 0, 0,                                 // Accumulation Bits Ignored
        16,                                         // 16Bit Z-Buffer (Depth Buffer)  
        0,                                          // No Stencil Buffer
        0,                                          // No Auxiliary Buffer
        PFD_MAIN_PLANE,                             // Main Drawing Layer
        0,                                          // Reserved
        0, 0, 0                                     // Layer Masks Ignored
    };

 //   dc = GetDC((HWND)window);
}

void arrows::systems::Renderer::term()
{
}

void arrows::systems::Renderer::addObject(graphics::Drawable* object)
{
	drawdata_.push_back(object);
}

void arrows::systems::Renderer::removeObject(graphics::Drawable* object)
{
	for (int i = 0; i < drawdata_.size(); i++)
	{
		if (drawdata_[i] == object) drawdata_.erase(drawdata_.begin() + i);
	}
}

void arrows::systems::Renderer::draw()
{
	for (int i = 0; i < drawdata_.size(); i++)
	{
		drawdata_[i]->draw_();
	}
}