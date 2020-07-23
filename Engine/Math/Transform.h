#pragma once

#include "Vector2.h"
#include <Math\Matrix33.h>
// iostream included with Vector2

namespace nc
{
	struct Transform
	{
		Vector2 position;
		float scale;
		float angle;

		Transform() : position{ 0, 0 }, scale{ 1 }, angle{ 0 } {}
		Transform(const Vector2& position, float scale = 0, float angle = 0) : position{ position }, scale{ scale }, angle{ angle } {}
		
		Matrix33 matrix;

		void Update();

		friend std::istream& operator >> (std::istream& stream, Transform& v);

	};
}