#include "Curve.h"
#include <Novice.h>
#include "VectorFunction.h"
#include "MatrixFunction.h"
Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t)
{
	Vector3 t0, t1;
	t0 = Lerp(p0, p1, t);
	t1 = Lerp(p1, p2, t);

	return Lerp(t0, t1, t);
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