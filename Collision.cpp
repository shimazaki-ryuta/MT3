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