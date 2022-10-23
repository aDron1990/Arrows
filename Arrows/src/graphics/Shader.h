#pragma once

#include "../resourñe/Resource.h"

namespace arrows::graphics
{
	class Shader : public Resource
	{
		friend class ResourceManager;

	private:

		unsigned int gl_id;
		void load_();
		void free_();

	public:

		void use();

	};
}