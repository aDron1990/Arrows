#pragma once

#include "kwee/core/api.h"

#include <glm/glm.hpp>

namespace kwee
{
	class Transformable
	{
	private:

		glm::mat4 transformMatrix_;

		glm::vec3 position_;
		glm::vec3 rotation_;
		glm::vec3 scale_;

		void updateMatrix();

	public:

		Transformable();

		void setPosition(glm::vec2 value);
		void setRotation(float value);
		void setScale(glm::vec2 value);

		glm::vec2 getPosition() const;
		float getRotation() const;
		glm::vec2 getScale() const;
		glm::mat4 getTransformMatrix() const;

	};
}