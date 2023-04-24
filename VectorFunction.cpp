#include <math.h>
#include <Novice.h>
#include "VectorFunction.h"

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return v;
}

Vector3 Subtruct(const Vector3& v1, const Vector3& v2)
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

Vector3 Nomalize(const Vector3& v)
{
	float length = Length(v);
	if (length == 0)
	{
		return v;
	}
	return Multiply((1.0f/length),v);
}

void VectorScreenPrintf(int x,int y, Vector3 v,const char* label)
{
	Novice::ScreenPrintf(x, y, "%6.02f", v.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%6.02f", v.y);
	Novice::ScreenPrintf(x + kColumnWidth*2, y, "%6.02f", v.z);
	Novice::ScreenPrintf(x + kColumnWidth*3, y, "%s", label);
}