#pragma once

#include <cmath>

// 3éüå≥ÉxÉNÉgÉã
class Vec3
{
public:
	float x;
	float y;
	float z;
public:
	Vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vec3(float posX, float posY, float posZ) 
	{
		x = posX;
		y = posY;
		z = posZ;
	}
	// Vec3 = (Vec3 += Vec3)
	Vec3 operator+=(const Vec3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	// Vec3 = Vec3 + Vec3
	Vec3 operator+(const Vec3& vec) const
	{
		Vec3 temp{ x + vec.x , y + vec.y , y + vec.z};
		return temp;
	}

	// Vec3 = (Vec3 -= Vec3)
	Vec3 operator-=(const Vec3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	// Vec3 = Vec3 - Vec3
	Vec3 operator-(const Vec3& vec) const
	{
		Vec3 temp{ x - vec.x , y - vec.y ,z - vec.z};
		return temp;
	}

	// Vec2 = (Vec2 *= float)
	Vec3 operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}
	// Vec2 = Vec2 * float
	Vec3 operator*(float scale) const
	{
		Vec3 temp{ x * scale , y * scale ,z * scale};
		return temp;
	}

	// Vec2 = (Vec2 /= float)
	Vec3 operator/=(float scale)
	{
		x /= scale;
		y /= scale;
		z /= scale;
		return *this;
	}
	// Vec2 = Vec2 / float
	Vec3 operator/(float scale) const
	{
		Vec3 temp{ x / scale , y / scale , z / scale };
		return temp;
	}

	// í∑Ç≥ÇÃéÊìæ
	float length()
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}

	// ê≥ãKâª Vec2 = Vec2.normalize()
	Vec3 normalize()
	{
		float len = length();
		if (len == 0)
		{
			return *this;
		}
		return (*this) / len;
	}
};