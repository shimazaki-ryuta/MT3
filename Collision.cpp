#include "Collision.h"
#include "VectorFunction.h"
#include <cmath>
bool IsCollision(const Sphere& s, const Plane& p)
{
	float k = (Dot(p.nomal,s.center)-p.distance);
	k = std::sqrtf(std::powf(k,2));
	Vector3 q = s.center - k * p.nomal;
	float distance = Length(q-s.center);
	if (distance <= s.radius)
	{
		return true;
	}
	return false;
}

bool IsCollision(const Segment& s, const Plane& p)
{
	float dot = Dot(s.diff, p.nomal);
	if (dot == 0)
	{
		return false;
	}
	float t = (p.distance - Dot(s.origin,p.nomal))/dot;
	if (t >= 0.0f && t <= 1.0f)
	{
		return true;
	}
	return false;
}