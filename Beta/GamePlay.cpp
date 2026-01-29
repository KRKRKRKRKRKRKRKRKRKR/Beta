#define _USE_MATH_DEFINES
#include <cmath>
#include "GamePlay.h"
#include <imgui.h>

GamePlay::GamePlay() {
	Init();
}



void GamePlay::Init() {
	//メインカメラの初期化
	CameraManager::GetInstance()->GetMainCamera().InitCameraTransform(mainCameraInfo, 1280.0f, 720.0f);
	
	uiCameraInfo.centerpos = { 640.0f,360.0f };
	//UIカメラの初期化
	CameraManager::GetInstance()->GetUICamera().InitCameraTransform(uiCameraInfo, 1280.0f, 720.0f);
	
	//ステージステータスの初期化
	GameConfig::GetInstance()->SetStageState(GameConfig::TOP);
	GameConfig::GetInstance()->SetPrevStageState(GameConfig::TOP);
	GameConfig::GetInstance()->SetCurrentStage(0);
	GameConfig::GetInstance()->SetCurrentWave(0);
	//カメラ回転角度の初期化
	currentCameraRotation_ = 0.0f;
	
	//プレイヤーの初期化
	player_.Init();

	//敵の初期化
	enemy_.Init(stage_.GetEnemySpawnRangeTransform());

	//UIの初期化
	ui_.Init();

	//コンボの初期化
	ComboManager::GetInstance()->ResetCombo();

	//スコアの初期化
	Score::GetInstance()->ResetScore();

	//ステージ回転の初期化
	cameraRotateEasing_.Init(0.0f, 0.0f, 60, EasingType::EASING_EASE_IN_OUT_QUAD);
	cameraRotateEasing_.easingRate = 0.0f;

	startDelayFrames_ = 60;   // e.g. 60 frames, 1 second at 60fps
	isStarting_ = true;
}


void GamePlay::Update(char* keys, char* preKeys) {
	// --- Camera shake logic (unchanged) ---
	if (cameraShakeDuration_ > 0.0f) {
		cameraShakeTime_ += 1.0f;
		float decay = 1.0f - (cameraShakeTime_ / cameraShakeDuration_);
		if (decay < 0.0f) decay = 0.0f;
		cameraShakeOffset_.x = (std::sinf(cameraShakeTime_ * 0.7f) + (rand() % 100 - 50) / 50.0f * 0.7f) * cameraShakePower_ * decay;
		cameraShakeOffset_.y = (std::cosf(cameraShakeTime_ * 1.2f) + (rand() % 100 - 50) / 50.0f * 0.7f) * cameraShakePower_ * decay;
		if (cameraShakeTime_ >= cameraShakeDuration_) {
			cameraShakeOffset_ = { 0.0f, 0.0f };
			cameraShakeDuration_ = 0.0f;
		}
	}
	else {
		cameraShakeOffset_ = { 0.0f, 0.0f };
	}

	// --- Collision/Shake/Slow-motion trigger (unchanged) ---
	bool isPlayerHit = PlayerIsHitEnemy();
	if (isPlayerHit && !wasPlayerHitInLastFrame_) {
		cameraShakeDuration_ = 10.0f;
		cameraShakePower_ = 6.0f;
		cameraShakeTime_ = 0.0f;

		timeScaleEasing_.Init(slowMotionTimeScale, normalTimeScale, slowMotionTime, EasingType::EASING_EASE_OUT_CUBIC);
		timeScaleEasing_.Start();

		printf("SHAKE TRIGGERED!\n");
	}
	wasPlayerHitInLastFrame_ = isPlayerHit;

	// --- Camera movement and transforms (unchanged) ---
	CameraManager::GetInstance()->GetMainCamera().SetCameraPosition(cameraBasePos_);
	CameraManager::GetInstance()->GetMainCamera().MoveCamera(cameraShakeOffset_);
	CameraControl();
	CameraManager::GetInstance()->UpdateAll();
	cameraRotateEasing_.Update();

	// --- Stage, Player, and UI always update ---
	player_.Update(keys, preKeys, stage_.GetTransform());
	WaveCountCheck();

	// --- Enemy start delay logic ---
	static int enemyStartDelayFrames = 60;       // 1 second delay at 60fps (update to match your variable if needed)

	// If you want to reset this on stage change or at Init, make enemyStartDelayFrames and isEnemySpawning member variables.
	if (!isEnemySpawning_) {
		if (enemyStartDelayFrames > 0) {
			--enemyStartDelayFrames; // Count down
			// Enemies NOT updated yet!
		}
		else {
			isEnemySpawning_ = true;
		}
	}

	// --- Enemy update and damage logic only after delay ---
	if (isEnemySpawning_) {
		enemy_.Update(stage_.GetEnemySpawnRangeTransform(), currentCameraRotation_, player_.IsOnGround());

		int damage = enemy_.GetNumZeroedThisTick();
		if (damage > 0) {
			int newHp = player_.GetHP() - damage;
			if (newHp < 0) newHp = 0;
			player_.SetHP(newHp);

			bg_.TriggerRedFlash();
			enemy_.ResetNumZeroedThisTick();
		}
	}

	timeScaleEasing_.Update();

	if (timeScaleEasing_.isMove) {
		GameConfig::GetInstance()->SetTimeScale(timeScaleEasing_.easingRate);
	}
	else {
		GameConfig::GetInstance()->SetTimeScale(normalTimeScale);
	}

	GameConfig::GetInstance()->ClearWaveChangedFlag();
	NextStageCheck();

	// --- UI always updated (score, combo, etc) ---
	ui_.Update(player_.GetTransform().worldPos, player_.GetHP());
}

//描画処理
void GamePlay::Draw() {
	bg_.Draw();
	bg_.DrawLogo();
	stage_.Draw();
	player_.Draw();
	if (isEnemySpawning_) {             // <-- Only draw after delay!
		enemy_.Draw();
	}
	ui_.Draw(player_.GetTransform(),currentCameraRotation_, player_.GetHP());
	//DebugText();

}

void GamePlay::DebugText() {
	ImGui::Begin("GamePlay::DebugText ");
	
	ImGui::Text("stage = %d", GameConfig::GetInstance()->GetCurrentStage());
	ImGui::Text("Wave = % d", GameConfig::GetInstance()->GetCurrentWave());
	ImGui::Text("Score = %d", Score::GetInstance()->GetDisplayScore());
	ImGui::Text("Combo = % d",ComboManager::GetInstance()->GetComboCount());
	ImGui::Text("StageState = %d", GameConfig::GetInstance()->GetStageState());
	ImGui::Text("Player HP = %d", player_.GetHP());
	ImGui::End();

}


//カメラ操作
void GamePlay::CameraControl() {

	GameConfig* config = GameConfig::GetInstance();
	
	//ステージの状態が変化したらカメラ回転イージング開始
	if (config->GetStageState() != config->GetPrevStageState() && !cameraRotateEasing_.isMove) {
		config->SetIsRotate(true);

		float start = fmodf(currentCameraRotation_, 360.0f);;
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

		// 最短経路の計算
		if (diff > 180.0f) {
			diff -= 360.0f;
		} else if (diff < -180.0f) {
			diff += 360.0f;
		}


		cameraRotateEasing_.Reset();
		cameraRotateEasing_.Init(start, start + diff, 60, EasingType::EASING_EASE_IN_OUT_QUAD);
		cameraRotateEasing_.Start();

		config->SetPrevStageState(config->GetStageState());
	}

	if (!cameraRotateEasing_.isMove) {
		config->SetIsRotate(false);
	}

	CameraManager::GetInstance()->GetMainCamera().SetCameraRotation(cameraRotateEasing_.easingRate);
	currentCameraRotation_ = cameraRotateEasing_.easingRate;
}

//プレイヤーが敵に当たったか
bool GamePlay::PlayerIsHitEnemy() {

	const Transform2D& playerTransform = player_.GetTransform();
	std::vector<Enemy::EnemyData>& enemies = enemy_.GetEnemies();

	for (auto& enemy : enemies) {
		if (!enemy.isActive) {
			continue;
		}
		if (collider_.AABB(playerTransform, enemy.transform)) {

			int maxEnemies = enemy_.GetMaxEnemyCount();
		
			ComboManager::GetInstance()->AddCombo();
			Score::GetInstance()->AddScore(maxEnemies);
			enemy.isActive = false; // 生存フラグをfalse
			player_.SetIsHitEnemy(true); // プレイヤーに当たりフラグを設定
			return true; // 衝突が検出された場合、trueを返す
		}
	}
	return false;
}

//次のステージへ進むかの判定
void GamePlay::NextStageCheck() {
	if (enemy_.IsAllDead()) {
		if (!isNextStageAdded) {
			GameConfig::GetInstance()->NextStage();
			GameConfig::GetInstance()->SetCurrentWave(-1); 

			isNextStageAdded = true;
		}
	} else {
		// 敵が復活したらフラグをリセット
		isNextStageAdded = false;
	}
}

void GamePlay::WaveCountCheck() {
	bool currentOnGround = player_.IsOnGround();
	GameConfig* config = GameConfig::GetInstance();

	if (!prePlayerOnGround && currentOnGround) {
		
		int nextWave = config->GetCurrentWave() + 1;
		config->SetCurrentWave(nextWave);
		ComboManager::GetInstance()->ResetCombo();
		combo = 0;
	}

	prePlayerOnGround = currentOnGround;


}

void GamePlay::SlowMotion() {
	timeScaleEasing_.Init(slowMotionTimeScale, normalTimeScale, slowMotionTime, EasingType::EASING_EASE_OUT_CUBIC);
	timeScaleEasing_.Start();
}

