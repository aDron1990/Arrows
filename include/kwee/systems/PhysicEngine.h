#pragma once

#include "kwee/game_primitives/Collider.h"

#include <vector>
#include <chrono>

namespace kwee
{
	class Rect
	{
	public:

		glm::vec2 v11 = glm::vec2(0.0f);
		glm::vec2 v12 = glm::vec2(0.0f);
		glm::vec2 v21 = glm::vec2(0.0f);
		glm::vec2 v22 = glm::vec2(0.0f);

		glm::vec2& operator[](int i)
		{
			switch (i)
			{
			case 0:
				return v11;
			case 1:
				return v12;
			case 2:
				return v21;
			case 3:
				return v22;
			case 4:
				return v11;
			default:
				throw;
			}
		}

	};
	
	class LineSegment
	{
	public:

		glm::vec2 p1;
		glm::vec2 p2;

	};

	class KWEEAPI PhysicEngine
	{
		friend class Application;

	private:

		static std::vector<Collider*> colliders_;
		static std::vector<int> requiedToRemoveCollidersIds_;

		static void removeRequiedObjects();

		static std::chrono::high_resolution_clock::time_point lastUpdateTime;
		static double delta;
		static long long milli;

	public:

		static void initialize();

		static void addCollider(Collider* c);
		static void removeCollider(Collider* c);

		static void update();
		static bool checkCollisions(Collider* c1, Collider* c2);
		static bool cross(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
		static float product(float Px, float Py, float Ax, float Ay, float Bx, float By);

		static double getDelta();
		static long long int millis();
	};
}
