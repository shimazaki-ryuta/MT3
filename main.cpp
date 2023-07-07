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

	OBB obb1{ .center{0,0,0}, .size{0.83f,0.26f,0.24f} };
	OBB obb2{ .center{0.9f,0.66f,0.78f}, .size{0.5f,0.37f,0.5f} };

	Vector3 rotate1{ 0.0f,0.0f,0.0f };
	Vector3 rotate2{ -0.05f,-2.49f,0.15f };

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
		
		Matrix4x4 rotateMatrix = MakeRotateMatrix(rotate1);
		SetOridentatios(obb1, rotateMatrix);
		rotateMatrix = MakeRotateMatrix(rotate2);
		SetOridentatios(obb2, rotateMatrix);


		//Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate,cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(debugCamera.GetWorld());
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f,float(kWindowWidth)/float(kWindowHeight),0.1f,100.0f);
		
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix,projectionMatrix);

		Matrix4x4 viewPortMatrix = MakeViewportMatrix(0,0,float(kWindowWidth) ,float(kWindowHeight),0.0f,1.0f);
		
		uint32_t color = WHITE;
		if (IsCollision(obb1,obb2))
		{
			color = RED;
		}
		
		ImGui::Begin("Window");
		//ImGui::DragFloat3("CameraTranslate",&cameraTranslate.x,0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("OBB1Center", &obb1.center.x, 0.01f);
		ImGui::DragFloat3("OBB1ORotate", &rotate1.x, 0.01f);
		ImGui::DragFloat3("OBB1Size", &obb1.size.x, 0.01f);
		ImGui::DragFloat3("OBB2Center", &obb2.center.x, 0.01f);
		ImGui::DragFloat3("OBB2ORotate", &rotate2.x, 0.01f);
		ImGui::DragFloat3("OBB2Size", &obb2.size.x, 0.01f);

		ImGui::End();
		//rotate = Normalize(rotate);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(viewProjectionMatrix,viewPortMatrix);
		DrawOBB(obb1, viewProjectionMatrix, viewPortMatrix, color);
		DrawOBB(obb2, viewProjectionMatrix, viewPortMatrix, WHITE);
		
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
