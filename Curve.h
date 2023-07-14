#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include <stdint.h>
#include <vector>
Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t);
void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color);
void DrawCatmullRom(std::vector<Vector3> controlPoints, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color);
