#pragma once

#include "Window.h"

#include <vector>

namespace arrows::graphics { class Drawable; }
namespace arrows::systems
{
	struct RendererState;
	static RendererState* state;

	static class Renderer
	{
	public:

		enum class RendererType
		{
			Software,
			Hardware
		};

	private:

		std::vector<graphics::Drawable*> drawdata_;
		RendererType type_;

		void initGDIRenderer(Window* window);
//		void initOpenGLRenderer();

	public:

		void init(Window* window, RendererType type);
		void term();

		void draw();

		void addObject(graphics::Drawable* object);
		void removeObject(graphics::Drawable* object);

	} renderer;
}