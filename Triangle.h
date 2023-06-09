#pragma once
#include <stdint.h>
#include "Vector3.h"
#include "Matrix4x4.h"
struct Triangle
{
	Vector3 vertices[3];
};

void DrawTriangle(const Triangle& t, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
