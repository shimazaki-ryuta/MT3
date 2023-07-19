#include <Novice.h>
#include <imgui.h>
#include <list>
#include "Vector3.h"
#include "VectorFunction.h"
#include "Matrix4x4.h"
#include "Matrix.h"
#include "MatrixFunction.h"

#include "MyDebugCamera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Collision.h"
#include "Draw3dStandard.h"
#include "AABB.h"
#include "OBB.h"

#include "Curve.h"
const char kWindowTitle[] = "LE2A_07_シマザキリュウタ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

const float kSpeed = 0.05f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//カメラ操作用
	/*int LeftClick = 0;
	int preLeftClick=0;
	Vector2 mousePosition;
	Vector2 preMousePosition;
	*/

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	DebugCamera debugCamera;
	debugCamera.Initialize({1.0f,1.0f,1.0f},cameraRotate,cameraTranslate);

	std::vector<Vector3> controlPoints = {
		{-0.8f,0.58f,1.0f},{1.76f,1.0f,-0.3f},{0.94f,-0.7f,2.3f},{-0.53f,-0.26f,-0.15f} };


	Vector3 translate[3] = {
		{0.2f,1.0f,0.0f},{0.4f,0.0f,0.0f},{0.3f,0.0f,0.0f}
	};

	Vector3 rotate[3] = {
		{0.0f,0.0f,-6.8f},{0.0f,0.0f,-1.4f},{0.0f,0.0f,0.0f}
	};

	Vector3 scale[3] = {
		{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f}
	};

	uint32_t color[3] = {RED,GREEN,BLUE};
	

	//Sphere sphere{ {1.0f,0.0f,0.0f},1.0f };
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		debugCamera.Update();
		
		

		//Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate,cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(debugCamera.GetWorld());
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f,float(kWindowWidth)/float(kWindowHeight),0.1f,100.0f);
		
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix,projectionMatrix);

		Matrix4x4 viewPortMatrix = MakeViewportMatrix(0,0,float(kWindowWidth) ,float(kWindowHeight),0.0f,1.0f);
		
		
		
		ImGui::Begin("Window");
		//ImGui::DragFloat3("CameraTranslate",&cameraTranslate.x,0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		for (int index = 0; index < 3; index++)
		{
			char tag[32];
			sprintf_s(tag,"Translate[%d]",index);
			ImGui::DragFloat3(tag, &translate[index].x, 0.01f);
			sprintf_s(tag, "Rotate[%d]", index);
			ImGui::DragFloat3(tag, &rotate[index].x, 0.01f);
			sprintf_s(tag, "Scale[%d]", index);
			ImGui::DragFloat3(tag, &scale[index].x, 0.01f);
		}
		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(viewProjectionMatrix,viewPortMatrix);
		Matrix4x4 parentWorld = MakeIdentity4x4();
		Vector3 world[3];
		for (int index = 0;index < 3;index++)
		{
			parentWorld =  MakeAffineMatrix(scale[index], rotate[index], translate[index]) * parentWorld;
			Sphere sphere = { .center{parentWorld.m[3][0],parentWorld.m[3][1],parentWorld.m[3][2]},.radius{0.05f} };
			world[index] = sphere.center;
			DrawSphere(sphere,viewProjectionMatrix,viewPortMatrix,color[index]);

		}
		Segment segment1 = { world[0],world[1] - world[0] };
		Segment segment2 = { world[1],world[2] - world[1] };
		DrawSegment(segment1, WHITE, viewProjectionMatrix, viewPortMatrix);
		DrawSegment(segment2, WHITE, viewProjectionMatrix, viewPortMatrix);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
