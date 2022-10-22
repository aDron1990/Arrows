#include "Window.h"
#include "Input.h"
#include "../mvc/App.h"
#include "Renderer.h"



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
	}

	return DefWindowProc(window, msg, wp, lp);
}

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

	SetWindowLongPtr(window_, GWLP_USERDATA, (LONG_PTR)mvc::App::getInstance());
}

arrows::systems::Window::~Window()
{
	DestroyWindow(window_);
}

HWND arrows::systems::Window::getWindow_()
{
	return window_;
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