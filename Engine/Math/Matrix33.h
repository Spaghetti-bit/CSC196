#pragma once
#include "Vector2.h"
#include "Math.h"

// Matrix 2 x 2
namespace nc
{
	struct Matrix33
	{
		float m[3][3]; // 3 x 3 / Column | Row
		// m[0][0] m[1][0] m[2][0]
		// m[0][1] m[1][1] m[2][1]
		// m[0][2] m[1][2] m[2][2]

		Matrix33() = default; // Matrix22() {}

		void Scale(float s)
		{
			m[0][0] =    s; m[1][0] = 0.0f; m[2][0] = 0.0f;
			m[0][1] = 0.0f; m[1][1] =    s; m[2][1] = 0.0f;
			m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
		}
		void Scale(float sx, float sy)
		{
			m[0][0] =   sx; m[1][0] = 0.0f; m[2][0] = 0.0f;
			m[0][1] = 0.0f; m[1][1] =   sy; m[2][1] = 0.0f;
			m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
		}
		void Scale(const Vector2& s)
		{
			m[0][0] =  s.x;  m[1][0] = 0.0f; m[2][0] = 0.0f;
			m[0][1] = 0.0f;  m[1][1] =  s.y; m[2][1] = 0.0f;
			m[0][2] = 0.0f;  m[1][2] = 0.0f; m[2][2] = 1.0f;
		}
		void Rotate(float angle)
		{
			m[0][0] =  std::cos(angle); m[1][0] = std::sin(angle); m[2][0] =  0.0f;
			m[0][1] = -std::sin(angle); m[1][1] = std::cos(angle); m[2][1] =  0.0f;
			m[0][2] =             0.0f; m[1][2] =            0.0f; m[2][2] =  1.0f;

		}
		void SetIdentity()
		{
			m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f;
			m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f;
			m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
		}

		// [ 1.0 0.0 0.0 ]
		// | 0.0 1.0 0.0 |
		// [ Tx  Ty  1.0 ]
		// Vx * 1.0 + Vy * 0.0 + 1.0 * Tx
		// Vx * 0.0 + Vy * 1.0 + 1.0 * Ty
		void Translate(const Vector2& v)
		{
			m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f;
			m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f;
			m[0][2] =  v.x; m[1][2] =  v.y; m[2][2] = 1.0f;

		}


		Matrix33 operator * (const Matrix33& mx)
		{
			Matrix33 result;
			result.m[0][0] = m[0][0] * mx.m[0][0] + m[1][0] * mx.m[0][1] + m[2][0] * mx.m[0][2]; // 0, 0
			result.m[0][1] = m[0][1] * mx.m[0][0] + m[1][1] * mx.m[0][1] + m[2][1] * mx.m[0][2]; // 0, 1
			result.m[0][2] = m[0][2] * mx.m[0][0] + m[1][2] * mx.m[0][1] + m[2][2] * mx.m[0][2]; // 0, 2

		
			result.m[1][0] = m[0][0] * mx.m[1][0] + m[1][0] * mx.m[1][1] + m[2][0] * mx.m[1][2]; // 1, 0
			result.m[1][1] = m[0][1] * mx.m[1][0] + m[1][1] * mx.m[1][1] + m[2][1] * mx.m[1][2]; // 1, 1
			result.m[1][2] = m[0][2] * mx.m[1][0] + m[1][2] * mx.m[1][1] + m[2][2] * mx.m[1][2]; // 1, 2 


			result.m[2][0] = m[0][0] * mx.m[2][0] + m[1][0] * mx.m[2][1] + m[2][0] * mx.m[2][2]; // 2, 0
			result.m[2][1] = m[0][1] * mx.m[2][0] + m[1][1] * mx.m[2][1] + m[2][1] * mx.m[2][2]; // 2, 1
			result.m[2][2] = m[0][2] * mx.m[2][0] + m[1][2] * mx.m[2][1] + m[2][2] * mx.m[2][2]; // 2, 2


			return result;

		}

		Vector2 operator * (const Vector2& v)
		{
			Vector2 result;

			result.x = v.x * m[0][0] + v.y * m[0][1] + m[0][2];
			result.y = v.x * m[1][0] + v.y * m[1][1] + m[1][2];

			return result;
		}

		friend Vector2 operator * (const Vector2& v, const Matrix33& mx)
		{
			Vector2 result;

			result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1] + mx.m[0][2];
			result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1] + mx.m[1][2];

			return result;

		}


	};
}