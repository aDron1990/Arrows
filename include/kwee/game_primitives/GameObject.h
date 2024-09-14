#pragma once

#include "Transformable.h"
#include "kwee/graphics/Mesh.h"
#include "kwee/graphics/Shader.h"
#include "kwee/graphics/Texture.h"
#include "kwee/graphics/Color.h"
#include "Collider.h"

#include <string>
#include <glm/glm.hpp>
#include <kwee/graphics/Shader.h>
#include <memory>

namespace kwee
{
	class Scene;
	class GameObject : public Transformable
	{
	private:

		std::shared_ptr<Shader> shader_;
		std::shared_ptr<Texture> texture_;
		std::shared_ptr<Mesh> mesh_;
		Scene* owner_;
		Collider* collider_ = 0;
		bool textured_;

	protected:

	public:

		Color color = { 0, 0, 0 };
		float mix = 0;
		float alpha = 1;
		bool colliderIsDrawing = false;
		bool visible = true;

		void createCollider(bool collisionSupport, bool mouseSupport);
		void deleteCollider();

		virtual void onCollision(Collider* other) {};
		virtual void onCollisionEnter(Collider* other) {};
		virtual void onCollisionExit(Collider* other) {};

		virtual void onMouseHover() {};
		virtual void onMouseHoverEnter() {};
		virtual void onMouseHoverExit() {};

		GameObject(kwee::Color color);
		GameObject(std::string textureName);
		virtual ~GameObject();

		void setOwnerScene(Scene* owner);
		Scene* getOwnerScene();

		void setTexture(std::shared_ptr<Texture> texture);
		std::shared_ptr<Texture> getTexture();

		void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
		virtual void update() {};
	};
}