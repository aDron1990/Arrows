#pragma once

#include <glm/glm.hpp>

namespace arrows::mvc
{
	class MCommand
	{
	public:

		enum class Action
		{
			LoadWorld,
			SetVoxel,
		};
		
		Action action;
		glm::vec2 voxelPos;
	};
}