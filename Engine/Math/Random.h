#pragma once
#include <cstdlib>
#include <cmath>
namespace nc
{
	float random() // 0.0 to 1.0
	{
		return rand() / static_cast<float>(RAND_MAX);
	}
	float random(float min, float max) // min - max
	{
		if (min > max)
		{
			float temp = min;
			min = max;
			max = temp;

			//std::swap(min, max);


		}


		return min + (max - min) * random();
	}
}