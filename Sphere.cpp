#include "Sphere.h"
#include "VectorFunction.h"
#include "MatrixFunction.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	float distance = Length(s2.center-s1.center);
	if (distance <= s1.radius + s2.radius)
	{
		return true;
	}
	return false;
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const uint32_t kSubdivision = 16;
	const float kLonEvery = float(M_PI) / float(kSubdivision) * 2.0f;
	const float kLatEvery = float(M_PI) / float(kSubdivision);

	Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);

	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);



	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex)
	{
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex)
		{
			float lon = lonIndex * kLonEvery;
			Vector3 a, b, c;
			a = { sphere.radius * cosf(lat) * cosf(lon)			,sphere.radius * sinf(lat),sphere.radius * cosf(lat) * sin(lon) };
			b = { sphere.radius * cosf(lat + kLatEvery) * cosf(lon),sphere.radius * sinf(lat + kLatEvery),sphere.radius * cosf(lat + kLatEvery) * sin(lon) };
			c = { sphere.radius * cosf(lat) * cosf(lon + kLonEvery),sphere.radius * sinf(lat),sphere.radius * cosf(lat) * sin(lon + kLonEvery) };

			Vector3 ndcA = Transform(a, worldViewProjectionMatrix);
			a = Transform(ndcA, viewportMatrix);
			Vector3 ndcB = Transform(b, worldViewProjectionMatrix);
			b = Transform(ndcB, viewportMatrix);
			Vector3 ndcC = Transform(c, worldViewProjectionMatrix);
			c = Transform(ndcC, viewportMatrix);

			Novice::DrawLine(int(a.x), int(a.y), int(b.x), int(b.y), color);
			Novice::DrawLine(int(a.x), int(a.y), int(c.x), int(c.y), color);

		}
	}
}