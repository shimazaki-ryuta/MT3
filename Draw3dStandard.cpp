#include "Draw3dStandard.h"
#include "MatrixFunction.h"
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

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const uint32_t kSubdivision = 32;
	const float kLonEvery = float(M_PI) / float(kSubdivision)*2.0f;
	const float kLatEvery = float(M_PI) / float(kSubdivision);

	Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);

	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);



	for (uint32_t latIndex = 0;latIndex < kSubdivision;++latIndex)
	{
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex)
		{
			float lon = lonIndex * kLonEvery;
			Vector3 a, b, c;
			a = {sphere.radius * cosf(lat)*cosf(lon)			,sphere.radius * sinf(lat),sphere.radius * cosf(lat)*sin(lon)};
			b = {sphere.radius * cosf(lat+kLatEvery) * cosf(lon),sphere.radius * sinf(lat+kLatEvery),sphere.radius * cosf(lat+kLatEvery) * sin(lon) };
			c = {sphere.radius * cosf(lat) * cosf(lon+kLonEvery),sphere.radius * sinf(lat),sphere.radius * cosf(lat) * sin(lon+kLonEvery) };

			Vector3 ndcA = Transform(a, worldViewProjectionMatrix);
			a = Transform(ndcA, viewportMatrix);
			Vector3 ndcB = Transform(b, worldViewProjectionMatrix);
			b = Transform(ndcB, viewportMatrix);
			Vector3 ndcC = Transform(c, worldViewProjectionMatrix);
			c = Transform(ndcC, viewportMatrix);

			Novice::DrawLine(int(a.x), int(a.y), int(b.x), int(b.y),color);
			Novice::DrawLine(int(a.x), int(a.y), int(c.x), int(c.y), color);

		}
	}
}