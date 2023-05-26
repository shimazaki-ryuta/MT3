#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"
class DebugCamera
{
private:
	Vector3 translate_, scale_, rotate_;
	Matrix4x4 worldMatrix_;
	
	int LeftClick = 0;
	int preLeftClick = 0;
	Vector2 mousePosition;
	Vector2 preMousePosition;

public:
	const float kSpeed = 0.05f;
	void Initialize(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
	void Update(char[]);
	
	inline Vector3 GetTranslate() { return translate_; };
	inline Vector3 GetScale() { return scale_; };
	inline Vector3 GetRotate() { return rotate_; };
	inline Matrix4x4 GetWorld() { return worldMatrix_; };
};

