#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace kwee
{
	class GameObject;
	class Collider
	{
		friend class PhysicEngine;

	private:
		
		bool lastUpdateHaveCollision = false;
		bool lastUpdateHaveMouseHover = false;
		bool collisionSupport_, mouseSupport_;

	protected:

		GLuint vbo_, vao_, ebo_;
		GameObject* owner_;
		std::vector<float> vertices_ = std::vector<float>({ 0.5,  0.5, 0.5, -0.5, -0.5, -0.5, -0.5,  0.5 });
		std::vector<int> indices_ = std::vector<int>({ 0, 1, 1, 2, 2, 3, 3, 0 });

	public:

		Collider(GameObject* owner, bool collisionSupport, bool mouseSupport);
		~Collider();
		
		virtual void resizeCollider(glm::vec2 value);
		virtual void updateBuffers();
		virtual void draw();

		GameObject* getOwner();

		void onCollision(Collider* other);
		void onCollisionEnter(Collider* other);
		void onCollisionExit(Collider* other);

		void onMouseHover();
		void onMouseHoverEnter();
		void onMouseHoverExit();
	};
}