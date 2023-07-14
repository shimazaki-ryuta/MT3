#include "Curve.h"
#include <Novice.h>
#include <algorithm>
#include "VectorFunction.h"
#include "MatrixFunction.h"
Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t)
{
	Vector3 t0, t1;
	t0 = Lerp(p0, p1, t);
	t1 = Lerp(p1, p2, t);

	return Lerp(t0, t1, t);
}

Vector3 CatmullRom(
	const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t) {
	Vector3 vector;
	vector = (-1*p0 + 3 * p1 - 3 * p2 + p3) * powf(t, 3) +
		(2 * p0 - 5 * p1 + 4 * p2 - p3) * powf(t, 2) + (-1*p0 + p2) * t + 2 * p1;
	return vector * (1.0f / 2.0f);
}

Vector3 CatmullRomComplement(std::vector<Vector3> controlPoints, float t)
{
	int pointsCount = int(controlPoints.size()) - 1;
	float divPoint = 1.0f / float(pointsCount);
	int section = int(t / divPoint);
	//float segmentT = t-(divPoint*float(section));
	float segmentT = (t - float(section) * divPoint) /
		(float(section + 1) * divPoint - float(section) * divPoint);
	return CatmullRom(
		controlPoints[std::clamp(section - 1, 0, pointsCount)], controlPoints[section],
		controlPoints[std::clamp(section + 1, 0, pointsCount)],
		controlPoints[std::clamp(section + 2, 0, pointsCount)], segmentT);
}

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color)
{
	const int SPLIT = 100;
	for (int i = 0; i < SPLIT; i)
	{
		float t0 = i++ / float(SPLIT);
		float t1 = i / float(SPLIT);
		Vector3 bezier0 = Bezier(controlPoint0, controlPoint1, controlPoint2, t0);
		Vector3 bezier1 = Bezier(controlPoint0, controlPoint1, controlPoint2, t1);

		bezier0 *= viewProjectionMatrix * viewPortMatrix;
		bezier1 *= viewProjectionMatrix * viewPortMatrix;
		Novice::DrawLine(int(bezier0.x),int( bezier0.y),int( bezier1.x),int( bezier1.y), color);
	}
}

void DrawCatmullRom(std::vector<Vector3> controlPoints, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color)
{
	std::vector<Vector3> pointsDrawing;
	const size_t segmentCount = 100;
	for (size_t i = 0; i < segmentCount + 1; i++)
	{
		float t = 1.0f / segmentCount * i;
		Vector3 pos = CatmullRomComplement(controlPoints, t);
		pos *= viewProjectionMatrix * viewPortMatrix;
		pointsDrawing.push_back(pos);
	}
	for (size_t i = 0; i < segmentCount; i++) {
		Novice::DrawLine(int(pointsDrawing[i].x), int(pointsDrawing[i].y), int(pointsDrawing[i + 1].x), int(pointsDrawing[i + 1].y), color);
	}

}