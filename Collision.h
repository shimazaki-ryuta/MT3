#pragma once
#include "Sphere.h"
#include "Vector3.h"
#include "Plane.h"
#include "Triangle.h"

bool IsCollision(const Sphere& s, const Plane& p);
bool IsCollision(const Segment& s, const Plane& p);
bool IsCollision(const Line& l, const Plane& p);
bool IsCollision(const Ray& r, const Plane& p);
bool IsCollision(const Triangle& t, const Segment& s);
bool IsCollision(const Triangle& t, const Line& l);
bool IsCollision(const Triangle& t, const Ray& r);
