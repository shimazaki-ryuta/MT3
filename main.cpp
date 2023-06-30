#include <Novice.h>
#include <imgui.h>
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

	OBB obb{ .center{-1.0f,0,0}, .size{0.5f,0.5f,0.5f} };
	Vector3 rotate{0.0f,0.0f,0.0f};
	Segment segment{ {-0.8f,0.3f,0.0f},{0.5f,0.5f,0.5f} };
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
		
		Matrix4x4 rotateMatrix = MakeRotateMatrix(rotate);
		SetOridentatios(obb,rotateMatrix);


		//Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate,cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(debugCamera.GetWorld());
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f,float(kWindowWidth)/float(kWindowHeight),0.1f,100.0f);
		
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix,projectionMatrix);

		Matrix4x4 viewPortMatrix = MakeViewportMatrix(0,0,float(kWindowWidth) ,float(kWindowHeight),0.0f,1.0f);
		
		uint32_t color = WHITE;
		if (IsCollision(obb, segment))
		{
			color = RED;
		}
		
		ImGui::Begin("Window");
		//ImGui::DragFloat3("CameraTranslate",&cameraTranslate.x,0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("OBBCenter", &obb.center.x, 0.01f);
		ImGui::DragFloat3("OBBORotate", &rotate.x, 0.01f);
		ImGui::DragFloat3("OBBSize", &obb.size.x, 0.01f);
		ImGui::DragFloat3("SegmentOrigin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("SegmentDiff", &segment.diff.x, 0.01f);

		ImGui::End();
		//rotate = Normalize(rotate);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(viewProjectionMatrix,viewPortMatrix);
		DrawOBB(obb, viewProjectionMatrix, viewPortMatrix,color);
		//DrawSphere(sphere, viewProjectionMatrix, viewPortMatrix,WHITE);
		DrawSegment(segment,WHITE, viewProjectionMatrix, viewPortMatrix);
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
