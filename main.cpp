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

const float deltaTime = 1.0f/60.0f;

struct Ball
{
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float mass;//質量kg
	float radius;
	unsigned int color;
};

struct Spring 
{
	Vector3 anchor;
	float naturalLength;
	float stiffness;
	float dampingCoefficient;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//カメラ操作用
	/*int LeftClick = 0;
	int preLeftClick=0;
	Vector2 mousePosition;
	Vector2 preMousePosition;
	*/

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	DebugCamera debugCamera;
	debugCamera.Initialize({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);

	bool Calclation = false;
	
	Spring spring;
	spring.anchor = {0.0f,1.0f,0.0f};
	spring.naturalLength = 0.7f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	Ball ball;
	ball.position = {0.8f,0.2f,0.0f};
	ball.velocity = {0.0f,0.0f,0.0f};
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	const Vector3 kGravity{0.0f,-9.8f,0.0f};

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
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);

		Matrix4x4 viewPortMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);


		if (Calclation)
		{
			Vector3 diff = ball.position - spring.anchor;
			float length = Length(diff);
			if (length != 0.0f)
			{
				Vector3 direction = Normalize(diff);
				Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
				Vector3 displacement = length * (ball.position - restPosition);
				Vector3 restoringForce = -spring.stiffness * displacement;
				Vector3 dampingForce = -spring.dampingCoefficient * ball.velocity;
				Vector3 force = restoringForce + dampingForce;
				ball.acceleration = force / ball.mass;
			}

			ball.velocity += (ball.acceleration + kGravity) * deltaTime;
			ball.position += ball.velocity * deltaTime;
		}




		ImGui::Begin("Window");
		if (ImGui::Button("Start"))
		{
			Calclation = true;
		}
		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewPortMatrix);
		Segment segment{spring.anchor,ball.position-spring.anchor};
		DrawSegment(segment,WHITE, viewProjectionMatrix, viewPortMatrix);
		Sphere sphere{ ball.position,ball.radius };
		DrawSphere(sphere, viewProjectionMatrix, viewPortMatrix,ball.color);
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
