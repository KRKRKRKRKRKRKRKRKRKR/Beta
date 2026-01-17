#include "GamePlay.h"

GamePlay::GamePlay() {

}

void GamePlay::Initialize() {
	Camera2D::cameraInfo cameraInfo;
	Camera2D::GetInstance()->InitCameraTransform(cameraInfo, 1280.0f, 720.0f);
	GameConfig::GetInstance()->SetStageState(GameConfig::TOP);
	GameConfig::GetInstance()->SetPrevStageState(GameConfig::TOP);
	currentCameraRotation_ = 0.0f;
	player_.Init();
}

void GamePlay::Update(char* keys, char* preKeys) {

	CameraControl(keys, preKeys);
	cameraRotateEasing_.Update();
	Camera2D::GetInstance()->MoveCameraTransform();
	player_.Update(keys, preKeys, stage_.GetTransform());

}

void GamePlay::Draw() {
	stage_.Draw();
	player_.Draw();
}
void GamePlay::CameraControl(char* keys, char* preKeys) {

	GameConfig* config = GameConfig::GetInstance();
	if (keys[DIK_0] || preKeys[DIK_9]) {

	}
	if (config->GetStageState() != config->GetPrevStageState() && !cameraRotateEasing_.isMove) {
		config->SetIsRotate(true);

		float start = currentCameraRotation_;
		float end = 0.0f;

		switch (config->GetStageState()) {
		case GameConfig::TOP:
			end = 0.0f;
			break;

		case GameConfig::BOTTOM:
			end = 180.0f;
			break;

		case GameConfig::LEFT:
			end = 270.0f;
			break;

		case GameConfig::RIGHT:
			end = 90.0f;
		}

		float diff = end - start;

		// 差が180度より大きい場合は、逆方向に回ったほうが速い
		if (diff > 180.0f) {
			end -= 360.0f; // 例: 270度なら -90度にする
		}
		else if (diff < -180.0f) {
			end += 360.0f; // 例: -270度なら 90度にする
		}


		cameraRotateEasing_.Reset();
		cameraRotateEasing_.Init(start, end, 60, EasingType::EASING_EASE_IN_OUT_QUAD);
		cameraRotateEasing_.Start();

		config->SetPrevStageState(config->GetStageState());
	}

	if (!cameraRotateEasing_.isMove) {
		config->SetIsRotate(false);
	}

	Camera2D::GetInstance()->SetCameraRotation(cameraRotateEasing_.easingRate);
	currentCameraRotation_ = cameraRotateEasing_.easingRate;
}

