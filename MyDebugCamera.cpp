#include "MyDebugCamera.h"
#include <Novice.h>
#include "VectorFunction.h"
#include "MatrixFunction.h"
void DebugCamera::Initialize(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	scale_ = scale;
	rotate_ = rotate;
	translate_ = translate;
}

void DebugCamera::Update()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	preLeftClick = LeftClick;
	LeftClick = Novice::IsPressMouse(1);
	if (LeftClick)
	{

		int x, y;
		Novice::GetMousePosition(&x, &y);
		mousePosition = { float(x),float(y) };
		if (preLeftClick)
		{
			Vector2 dragLength = mousePosition - preMousePosition;
			rotate_.x += dragLength.y * 0.005f;
			rotate_.y += dragLength.x * 0.005f;

		}
		preMousePosition = mousePosition;
	}
	Vector3 move{ 0.0f,0.0f,0.0f };
	if (keys[DIK_A])
	{
		move.x--;
	}
	if (keys[DIK_D])
	{
		move.x++;
	}
	if (keys[DIK_S])
	{
		move.z--;
	}
	if (keys[DIK_W])
	{
		move.z++;
	}
	if (keys[DIK_Q])
	{
		translate_.y -= kSpeed;
	}
	if (keys[DIK_E])
	{
		translate_.y += kSpeed;
	}
	Vector3 xMasked{ 0.0f,rotate_.y ,rotate_.z };
	translate_ += Transform(kSpeed*Normalize(move), MakeRotateMatrix(xMasked));
	worldMatrix_ = MakeAffineMatrix(scale_,rotate_,translate_);
}
