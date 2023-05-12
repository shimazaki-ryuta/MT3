#include <Novice.h>
#include "Vector3.h"
#include "VectorFunction.h"
#include "Matrix4x4.h"
#include "Matrix.h"
#include "MatrixFunction.h"
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

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1,v2);

	Vector3 kLocalVertices[3]{ {0.0f,1.0f,0.0f},{0.5f,-0.5f,0.0f},{-0.5f,-0.5f,0.0f} };

	Vector3 rotate{0.0f,0.0f,0.0f};
	Vector3 translate{0.0f,0.0f,5.0f};

	Vector3 cameraPosition{ 0.0f,0.0f,0.0f };
	Vector3 cameraRotate{ 0.0f,0.0f,0.0f };

	

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
		if (keys[DIK_A])
		{
			translate.x -= kSpeed;
		}
		if (keys[DIK_D])
		{
			translate.x += kSpeed;
		}
		if (keys[DIK_S])
		{
			translate.z -= kSpeed;
		}
		if (keys[DIK_W])
		{
			translate.z += kSpeed;
		}
		rotate.y += kSpeed;
		//rotate.y = 0.0f;
		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f,1.0f,1.0f},rotate,translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f },cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f,float(kWindowWidth)/float(kWindowHeight),0.1f,100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix,Multiply(viewMatrix,projectionMatrix));
		Matrix4x4 viewPortMatrix = MakeViewportMatrix(0,0,float(kWindowWidth) ,float(kWindowHeight),0.0f,1.0f);
		Vector3 screenVertices[3];
		Vector3 worldVertices[3];

		for (uint32_t i=0;i<3;++i)
		{
			Vector3 ndcVertex = Transform(kLocalVertices[i],worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex,viewPortMatrix);
			worldVertices[i] = Transform(kLocalVertices[i],worldMatrix);
		}
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		VectorScreenPrintf(0,0,cross,"Cross");
		float culling = Dot({ 0.0f,0.0f,1.0f }, Cross(Subtruct(worldVertices[1], worldVertices[0]), Subtruct(worldVertices[2], worldVertices[1])));
		if (culling<=0.0f)
		{
			Novice::DrawTriangle(int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y),
				int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid);
		}
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
