#pragma once
#include <Vector3.h>
#include <Matrix4x4.h>
#include <stdint.h>

void DrawGrid(const Matrix4x4& viewProjectionMatrix,const Matrix4x4& viewportMatrix);
void DrawSegment(const Segment& s, uint32_t color, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
