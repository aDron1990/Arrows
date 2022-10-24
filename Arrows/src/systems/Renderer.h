#pragma once

#include "Window.h"
#include "../graphics/Shader.h"

#include <vector>

namespace arrows::graphics { class Drawable; }
namespace arrows::systems
{
	struct RendererState;
	static RendererState* state;

	static class Renderer
	{
	private:

		std::vector<graphics::Drawable*> drawdata_;

	public:

		graphics::Shader shader;
		unsigned int vbo, vao;

		void init(glm::ivec2 viewportSize);
		void term();

		void draw();

		void addObject(graphics::Drawable* object);
		void removeObject(graphics::Drawable* object);

	} renderer;
}