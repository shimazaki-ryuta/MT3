#include <math.h>
#include <Novice.h>
#include "VectorFunction.h"
#include <cmath>
#include <algorithm>

Vector2 Add(const Vector2& v1, const Vector2& v2)
{
	Vector2 v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return v;
}
Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return v;
}

Vector2 Subtract(const Vector2& v1, const Vector2& v2)
{
	Vector2 v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return v;
}
Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return v;
}

Vector3 Multiply(float scalar, const Vector3& v)
{
	Vector3 returnV;
	returnV.x = v.x * scalar;
	returnV.y = v.y * scalar;
	returnV.z = v.z * scalar;
	return returnV;
}

float Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float Length(const Vector3& v)
{
	return sqrtf(Dot(v,v));
}

Vector3 Normalize(const Vector3& v)
{
	float length = Length(v);
	if (length == 0)
	{
		return v;
	}
	return Multiply((1.0f/length),v);
}
Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	return {v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y -v1.y*v2.x};
}

Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	return Multiply(Dot(v1, Normalize(v2)), Normalize(v2));
}

Vector3 ClosestPoint(const Vector3& point, const Line& line)
{
	Vector3 a = Subtract(point, line.origin);
	Vector3 b = line.diff;
	float t = Dot(a, b) / float(std::pow(Length(b), 2));
	return Add(line.origin, Multiply(t, b));
}
Vector3 ClosestPoint(const Vector3& point, const Ray& ray)
{
	Vector3 a = Subtract(point, ray.origin);
	Vector3 b = ray.diff;
	float t = Dot(a, b) / float(std::pow(Length(b), 2));
	t=std::clamp(t, 0.0f, t);
	return Add(ray.origin, Multiply(t, b));
}
Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	Vector3 a = Subtract(point, segment.origin);
	Vector3 b = segment.diff;
	float t = Dot(a, b) / float(std::pow(Length(b),2));
	t=std::clamp(t,0.0f,1.0f);
	return Add(segment.origin,Multiply(t,b));
}

void VectorScreenPrintf(int x,int y, Vector3 v,const char* label)
{
	Novice::ScreenPrintf(x, y, "%6.02f", v.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%6.02f", v.y);
	Novice::ScreenPrintf(x + kColumnWidth*2, y, "%6.02f", v.z);
	Novice::ScreenPrintf(x + kColumnWidth*3, y, "%s", label);
}

Vector2 operator+(const Vector2& v1, const Vector2& v2) { return Add(v1, v2); }
Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }
Vector2 operator-(const Vector2& v1, const Vector2& v2) { return Subtract(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
Vector3 operator*(float k, const Vector3& v) { return Multiply(k, v); }
Vector3 operator*(const Vector3& v, float k) { return Multiply(k, v); }

Vector3 operator+=(Vector3& v1, Vector3& v2) { return v1 = Add(v1, v2); }
Vector3 operator+=(Vector3& v1, const Vector3& v2) { return v1 = Add(v1, v2); }

Vector3 operator-=(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
