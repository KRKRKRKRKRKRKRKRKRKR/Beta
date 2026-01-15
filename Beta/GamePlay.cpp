#include "GamePlay.h"

GamePlay::GamePlay() {

}

void GamePlay::Initialize() {
	Camera2D::cameraInfo cameraInfo;
	Camera2D::GetInstance()->InitCameraTransform(cameraInfo, 1280.0f, 720.0f);

	currentCameraRotation_ = 0.0f;

	player_.Init();
}

void GamePlay::Update(char* keys, char* preKeys) {

	CameraControl(keys,preKeys);
	cameraRotateEasing_.Update();
	Camera2D::GetInstance()->MoveCameraTransform();
	player_.Update(keys, preKeys);
}

void GamePlay::Draw() {
	stage_.Draw();
	Transform2D testBox;

	testBox.Init({ 640.0f,500.0f }, 50.0f, 50.0f);

	Quad screen = Camera2D::GetInstance()->WorldToScreen(testBox);

	Novice::DrawQuad(static_cast<int>(screen.v[0].x), static_cast<int>(screen.v[0].y), static_cast<int>(screen.v[1].x), static_cast<int>(screen.v[1].y), static_cast<int>(screen.v[2].x), static_cast<int>(screen.v[2].y), static_cast<int>(screen.v[3].x), static_cast<int>(screen.v[3].y), 0, 0, static_cast<int>(testBox.width), static_cast<int>(testBox.height), Novice::LoadTexture("./BOX.png"), BLACK);

	Novice::ScreenPrintf(0, 50, "Camera Rotation: %.2f", Camera2D::GetInstance()->GetCameraInfo().rotation);
	Novice::ScreenPrintf(0, 70, "Camera State: %s", (stageState_ == TOP ? "TOP is UP" : "BOTTOM is UP"));
}

// ƒJƒƒ‰‘€ì
void GamePlay::CameraControl(char * keys,char * preKeys) {

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && !cameraRotateEasing_.isMove) {
		if (currentCameraRotation_ >= 360.0f) {
			currentCameraRotation_ = 0.0f;
		}

		float start = currentCameraRotation_;
		float end = 0.0f;

		switch (stageState_) {
		case TOP:
			stageState_ = BOTTOM;
			end = 180.0f;
			break;
		case BOTTOM:
			stageState_ = TOP;
			end = 360.0f;
			break;
		}

		cameraRotateEasing_.Reset();
		cameraRotateEasing_.Init(start, end, 60, EasingType::EASING_EASE_IN_OUT_QUAD);
		cameraRotateEasing_.Start();
	}

	Camera2D::GetInstance()->SetCameraRotation(cameraRotateEasing_.easingRate);
	currentCameraRotation_ = cameraRotateEasing_.easingRate;
}

