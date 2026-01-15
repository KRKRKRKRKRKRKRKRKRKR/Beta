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

	CameraControl(keys, preKeys);
	cameraRotateEasing_.Update();
	Camera2D::GetInstance()->MoveCameraTransform();
	player_.Update(keys, preKeys);
	player_.SetHitStage(collider_.Clamp(player_.transform, stage_.GetTransform()));
	
}

void GamePlay::Draw() {
	stage_.Draw();
	player_.Draw();

	Novice::ScreenPrintf(0, 50, "Camera Rotation: %.2f", Camera2D::GetInstance()->GetCameraInfo().rotation);
	Novice::ScreenPrintf(0, 70, "Camera State: %s", (GameConfig::GetInstance()->GetStageState() == GameConfig::TOP ? "TOP is UP" : "BOTTOM is UP"));
	Novice::ScreenPrintf(0, 90, "Camera isMove: %s", (GameConfig::GetInstance()->GetIsRotate() == true ? "Move" : "Stop"));
}
void GamePlay::CameraControl(char* keys, char* preKeys) {

	GameConfig* config = GameConfig::GetInstance();

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && !cameraRotateEasing_.isMove) {
		config->SetIsRotate(true);

		if (currentCameraRotation_ >= 360.0f) {
			currentCameraRotation_ = 0.0f;
		}

		float start = currentCameraRotation_;
		float end = 0.0f;

		switch (config->GetStageState()) {

		case GameConfig::TOP:
			config->SetStageState( GameConfig::BOTTOM);
			end = 180.0f;
			break;

		case GameConfig::BOTTOM:
			config->SetStageState (GameConfig::TOP);
			end = 360.0f;
			break;
		}

		cameraRotateEasing_.Reset();
		cameraRotateEasing_.Init(start, end, 60, EasingType::EASING_EASE_IN_OUT_QUAD);
		cameraRotateEasing_.Start();
	}


	if (!cameraRotateEasing_.isMove) {
		config->SetIsRotate(false);
	}

	Camera2D::GetInstance()->SetCameraRotation(cameraRotateEasing_.easingRate);
	currentCameraRotation_ = cameraRotateEasing_.easingRate;
}

