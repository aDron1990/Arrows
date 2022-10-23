#include "Window.h"
#include "Input.h"
#include "../mvc/App.h"
#include "Renderer.h"

#include <Windows.h>
#include <gl/GL.h>

LRESULT CALLBACK WndProc(HWND window, UINT msg, WPARAM wp, LPARAM lp);

namespace
{
	bool classRegistered = false;
	WNDCLASSEX wcex = { 0 };
	void registerClass()
	{
		wcex.lpszClassName = "ArrowsWindow";
		wcex.hInstance = GetModuleHandle(0);
		wcex.cbSize = sizeof(wcex);
		wcex.lpfnWndProc = WndProc;
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		if (!RegisterClassEx(&wcex)) throw;
	}
	static HWND window_;
	static HDC dc_;
	static HGLRC glrc_;
}

LRESULT CALLBACK WndProc(HWND window, UINT msg, WPARAM wp, LPARAM lp)
{
	WORD keyFlags = HIWORD(lp);
	bool repeat = (keyFlags & KF_REPEAT) == KF_REPEAT;

	switch (msg)
	{
		case WM_KEYDOWN:	if (!repeat) arrows::systems::parse_key_input(wp, true);	break;
		case WM_KEYUP:		if (!repeat) arrows::systems::parse_key_input(wp, false);	break;
		case WM_CLOSE: 
		{
			arrows::mvc::App::getInstance()->getController()->sendCommand(arrows::mvc::Controller::CCommand::Close);

			return 0;
		}

		case WM_CREATE:
		{
			dc_ = GetDC(window);

			PIXELFORMATDESCRIPTOR pfd = {
				sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd  
				1,                                // version number  
				PFD_DRAW_TO_WINDOW |              // support window  
				PFD_SUPPORT_OPENGL |              // support OpenGL  
				PFD_DOUBLEBUFFER,                 // double buffered  
				PFD_TYPE_RGBA,                    // RGBA type  
				24,                               // 24-bit color depth  
				0, 0, 0, 0, 0, 0,                 // color bits ignored  
				0,                                // no alpha buffer  
				0,                                // shift bit ignored  
				0,                                // no accumulation buffer  
				0, 0, 0, 0,                       // accum bits ignored  
				32,                               // 32-bit z-buffer      
				0,                                // no stencil buffer  
				0,                                // no auxiliary buffer  
				PFD_MAIN_PLANE,                   // main layer  
				0,                                // reserved  
				0, 0, 0                           // layer masks ignored  
			};

			int  iPixelFormat;

			iPixelFormat = ChoosePixelFormat(dc_, &pfd);
			SetPixelFormat(dc_, iPixelFormat, &pfd);

			if (glrc_ = wglCreateContext(dc_))
			{
				wglMakeCurrent(dc_, glrc_);
			}
		} 
		
		break;
		
		case WM_DESTROY:
		{
			wglDeleteContext(glrc_);
			ReleaseDC(window, dc_);
		}

		break;

		case WM_PAINT:
			arrows::systems::renderer.draw();
			PAINTSTRUCT ps;
			BeginPaint(window, &ps);
			EndPaint(window, &ps);
			return 0;
	}

	return DefWindowProc(window, msg, wp, lp);
}

arrows::systems::Window::Window(std::string name, int width, int height)
{
	if (!classRegistered) registerClass();

	DWORD style = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX;

	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, style, false);
	window_ = CreateWindowEx(0, wcex.lpszClassName, name.c_str(), style,
		200, 200, rect.right - rect.left, rect.bottom - rect.top, 0, 0, wcex.hInstance, 0);
	if (window_ == nullptr) throw;
	ShowWindow(window_, SW_SHOW);

	SetWindowLongPtr(window_, GWLP_USERDATA, (LONG_PTR)this);
}

arrows::systems::Window::~Window()
{
	DestroyWindow(window_);
}

namespace { MSG msg = { 0 }; }
void arrows::systems::Window::pollEvents()
{
	if (PeekMessage(&msg, window_, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void arrows::systems::Window::swapBuffers()
{
	SwapBuffers(dc_);
}

glm::vec2 arrows::systems::Window::getViewportSize()
{
	RECT rect;
	GetClientRect(window_, &rect);
	return glm::vec2{ rect.right - rect.left, rect.bottom - rect.top };
}