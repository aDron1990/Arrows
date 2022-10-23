#pragma once

#include <string>

namespace arrows
{
	namespace systems { class ResourceManager; }
	class Resource
	{
		friend class systems::ResourceManager;

	private:
		
		enum class ResourceType
		{
			Shader, Image, Save, Log
		};

		ResourceType type_;
		std::string name_;
	};
}