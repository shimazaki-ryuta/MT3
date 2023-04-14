#pragma once
#include <Vector3.h>
#include "Matrix.h"
Vector3 Add(const Vector3&, const Vector3&);
Vector3 Subtruct(const Vector3&, const Vector3&);
Vector3 Multiply(float , const Vector3&);
float Dot(const Vector3&, const Vector3&);
float Length(const Vector3&);
Vector3 Nomalize(const Vector3&);

void VectorScreenPrintf(int x, int y, Vector3 v, const char* label);