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

bool IsCollision(const Line& l, const Plane& p)
{
	float dot = Dot(l.diff, p.nomal);
	if (dot == 0)
	{
		return false;
	}
	return true;
}

bool IsCollision(const Ray& r, const Plane& p)
{
	float dot = Dot(r.diff, p.nomal);
	if (dot == 0)
	{
		return false;
	}
	float t = (p.distance - Dot(r.origin, p.nomal)) / dot;
	if (t >= 0.0f)
	{
		return true;
	}
	return false;
}

bool IsCollision(const Triangle& triangle, const Segment& s)
{
	Plane plane;
	Vector3 v1=(triangle.vertices[1] - triangle.vertices[0]), v2=(triangle.vertices[2]-triangle.vertices[1]),v3=(triangle.vertices[0]-triangle.vertices[2]);
	plane.nomal = Normalize(Cross(v1,v2));
	plane .distance = Dot(triangle.vertices[0], plane.nomal);

	if (!IsCollision(s, plane))
	{
		return false;
	}
	float dot = Dot(s.diff, plane.nomal);
	float t = (plane.distance - Dot(s.origin, plane.nomal)) / dot;
	
	Vector3 p = s.origin + t * s.diff;
	Vector3 cross1 = Cross(v1, Vector3(p - triangle.vertices[1]));
	Vector3 cross2 = Cross(v2, Vector3(p - triangle.vertices[2]));
	Vector3 cross3 = Cross(v3, Vector3(p - triangle.vertices[0]));
	float dot1 = Dot(cross1, plane.nomal);
	float dot2 = Dot(cross2, plane.nomal);
	float dot3 = Dot(cross3, plane.nomal);
	if (dot1 >= 0.0f && dot2 >= 0.0f && dot3 >= 0.0f)
	{
		return true;
	}
	return false;
}

bool IsCollision(const Triangle& triangle, const Line& l)
{
	Plane plane;
	Vector3 v1 = (triangle.vertices[1] - triangle.vertices[0]), v2 = (triangle.vertices[2] - triangle.vertices[1]), v3 = (triangle.vertices[0] - triangle.vertices[2]);
	plane.nomal = Normalize(Cross(v1, v2));
	plane.distance = Dot(triangle.vertices[0], plane.nomal);

	if (!IsCollision(l, plane))
	{
		return false;
	}
	float dot = Dot(l.diff, plane.nomal);
	float t = (plane.distance - Dot(l.origin, plane.nomal)) / dot;

	Vector3 p = l.origin + t * l.diff;
	Vector3 cross1 = Cross(v1, Vector3(p - triangle.vertices[1]));
	Vector3 cross2 = Cross(v2, Vector3(p - triangle.vertices[2]));
	Vector3 cross3 = Cross(v3, Vector3(p - triangle.vertices[0]));
	float dot1 = Dot(cross1, plane.nomal);
	float dot2 = Dot(cross2, plane.nomal);
	float dot3 = Dot(cross3, plane.nomal);
	if (dot1 >= 0.0f && dot2 >= 0.0f && dot3 >= 0.0f)
	{
		return true;
	}
	return false;
}

bool IsCollision(const Triangle& triangle, const Ray& r)
{
	Plane plane;
	Vector3 v1 = (triangle.vertices[1] - triangle.vertices[0]), v2 = (triangle.vertices[2] - triangle.vertices[1]), v3 = (triangle.vertices[0] - triangle.vertices[2]);
	plane.nomal = Normalize(Cross(v1, v2));
	plane.distance = Dot(triangle.vertices[0], plane.nomal);

	if (!IsCollision(r, plane))
	{
		return false;
	}
	float dot = Dot(r.diff, plane.nomal);
	float t = (plane.distance - Dot(r.origin, plane.nomal)) / dot;

	Vector3 p = r.origin + t * r.diff;
	Vector3 cross1 = Cross(v1, Vector3(p - triangle.vertices[1]));
	Vector3 cross2 = Cross(v2, Vector3(p - triangle.vertices[2]));
	Vector3 cross3 = Cross(v3, Vector3(p - triangle.vertices[0]));
	float dot1 = Dot(cross1, plane.nomal);
	float dot2 = Dot(cross2, plane.nomal);
	float dot3 = Dot(cross3, plane.nomal);
	if (dot1 >= 0.0f && dot2 >= 0.0f && dot3 >= 0.0f)
	{
		return true;
	}
	return false;
}
