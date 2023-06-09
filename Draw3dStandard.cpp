#include "Draw3dStandard.h"
#include "MatrixFunction.h"
#include "VectorFunction.h"
#include "Vector4.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivison = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivison);

	for (uint32_t xIndex = 0;xIndex <= kSubdivison;++xIndex)
	{
		Vector3 start(float(xIndex)*kGridEvery-kGridHalfWidth,0.0f,-kGridHalfWidth), end(float(xIndex) * kGridEvery - kGridHalfWidth, 0.0f, kGridHalfWidth);
		Vector3 translate(0.0f,0.0f,0.0f);
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, translate);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

		Vector3 ndcStart = Transform(start, worldViewProjectionMatrix);
		start = Transform(ndcStart, viewportMatrix);

		Vector3 ndcEnd = Transform(end, worldViewProjectionMatrix);
		end = Transform(ndcEnd, viewportMatrix);

		uint32_t color = 0xAAAAAAFF;
		if (xIndex == kSubdivison/2)
		{
			color = 0x000000FF;
		}
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y),color);
	}
	for (uint32_t zIndex = 0; zIndex <= kSubdivison; ++zIndex)
	{
		Vector3 start(-kGridHalfWidth, 0.0f, float(zIndex) * kGridEvery-kGridHalfWidth), end(kGridHalfWidth, 0.0f, float(zIndex) * kGridEvery - kGridHalfWidth);
		Vector3 translate(0.0f, 0.0f, 0.0f);
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, translate);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

		Vector3 ndcStart = Transform(start, worldViewProjectionMatrix);
		start = Transform(ndcStart, viewportMatrix);

		Vector3 ndcEnd = Transform(end, worldViewProjectionMatrix);
		end = Transform(ndcEnd, viewportMatrix);

		uint32_t color = 0xAAAAAAFF;
		if (zIndex == kSubdivison / 2)
		{
			color = 0x000000FF;
		}
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
	}
}

void DrawSegment(const Segment& s,uint32_t color, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	Vector3 screenOrigin, screenEnd;
	Vector3 ndcVertex;
	ndcVertex = Transform(s.origin, viewProjectionMatrix);
	screenOrigin = Transform(ndcVertex, viewportMatrix);
	ndcVertex = Transform(Add(s.origin, s.diff), viewProjectionMatrix);
	screenEnd = Transform(ndcVertex, viewportMatrix);
	Novice::DrawLine(int(screenOrigin.x), int(screenOrigin.y), int(screenEnd.x), int(screenEnd.y), color);
}

