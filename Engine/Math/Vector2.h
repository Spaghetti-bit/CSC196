#pragma once

#include <cmath>
#include <istream>

namespace nc
{
	struct Vector2
	{
		float x, y;

		Vector2() : x{ 0 }, y{ 0 } {};
		Vector2(float x, float y) : x{ x }, y{ y } {};
		Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) } {};


		float& operator [] (size_t index) { return (&x)[index]; }
		const float& operator [] (size_t index) const { return (&x)[index]; }

		void set(float x, float y) { this->x = x; this->y = y; }

		Vector2 operator + (const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
		Vector2 operator - (const Vector2& other) const { return Vector2(x - other.x, y - other.y); }

		Vector2 operator * (const Vector2& other) const { return Vector2(x * other.x, y * other.y); }
		Vector2 operator / (const Vector2& other) const { return Vector2(x / other.x, y / other.y); }


		Vector2 operator + (float s) const { return Vector2(x + s, y + s); }
		Vector2 operator - (float s) const { return Vector2(x - s, y - s); }

		Vector2 operator * (float s) const { return Vector2(x * s, y * s); }
		Vector2 operator / (float s) const { return Vector2(x / s, y / s); }

		Vector2 operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2 operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }

		Vector2 operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2 operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		Vector2 operator += (float s) { x += s; y += s; return *this; }
		Vector2 operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2 operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2 operator /= (float s) { x /= s; y /= s; return *this; }

		Vector2 operator - () { return *this * -1; }


		friend std::istream& operator >> (std::istream& stream, Vector2& v);


		float Length() const;
		float LengthSqr() const;

		Vector2 Normalized() const;
		void Normalize();


		static float Distance(const Vector2& v1, const Vector2& v2);
		static Vector2 Rotate(const Vector2& v, float radians);

		static const Vector2 left; 
		static const Vector2 right;
		static const Vector2 up;
		static const Vector2 down;

		static const Vector2 forward;

	};


	inline float Vector2::Length() const
	{
		return std::sqrt((x * x) + (y * y));
	}
	inline float Vector2::LengthSqr() const
	{
		return ((x * x) + (y * y));
	}

	inline Vector2 Vector2::Normalized() const
	{
		float length = Length();
		Vector2 n = (length == 0.0f) ? Vector2{ 0.0f,0.0f } : *this / length;

		return n;
	}

	inline void Vector2::Normalize()
	{
		float length = Length();
		if (length == 0.0f)
		{
			x = y = 0.0f;
		}
		else
		{
			*this /= length;
		}
	}

	inline float Vector2::Distance(const Vector2& v1, const Vector2& v2)
	{
		Vector2 v = v1 - v2;
		return v.Length();
	}

	inline Vector2 Vector2::Rotate(const Vector2& v, float radians)
	{
		float x = v.x * std::cos(radians) - v.y * std::sin(radians);
		float y = v.x * std::sin(radians) + v.y * std::cos(radians);

		return { x,y };
	}
}