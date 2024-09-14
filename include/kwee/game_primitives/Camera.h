#pragma once

#include "kwee/core/api.h"
#include "Transformable.h"

#include <glm/glm.hpp>

namespace kwee
{
	class Camera
	{
	private:

		glm::mat4 projection_;
		glm::vec4 viewport_;
		float aspect_;

		glm::mat4 transformMatrix_;

		glm::vec3 position_;
		glm::vec3 rotation_;
		glm::vec3 scale_;

		void updateMatrix();

	public:

		Camera(glm::vec4 viewport);
		~Camera() = default;

		void setPosition(glm::vec2 value);
		void setRotation(float value);
		void setScale(glm::vec2 value);

		glm::vec2 getPosition() const;
		float getRotation() const;
		glm::vec2 getScale() const;
		glm::mat4 getTransformMatrix() const;

		void setVieport(glm::vec4 viewport);

		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();
		void useViewport();

		glm::vec2 ScreenToWorld(glm::fvec2 screenCoords);

	};
}