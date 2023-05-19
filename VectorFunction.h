#pragma once
#include "Vector3.h"
#include "Matrix.h"
Vector3 Add(const Vector3&, const Vector3&);
Vector3 Subtract(const Vector3&, const Vector3&);
Vector3 Multiply(float , const Vector3&);
float Dot(const Vector3&, const Vector3&);
float Length(const Vector3&);
Vector3 Normalize(const Vector3&);
Vector3 Cross(const Vector3& v1, const Vector3& v2);

Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 ClosestPoint(const Vector3& point, const Line& Line);
Vector3 ClosestPoint(const Vector3& point, const Ray& Ray);
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

void VectorScreenPrintf(int x, int y, Vector3 v, const char* label);