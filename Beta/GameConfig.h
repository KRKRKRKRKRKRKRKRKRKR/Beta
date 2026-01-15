#pragma once

class GameConfig {
public:
	static GameConfig* GetInstance() {
		static GameConfig instance;
		return &instance;
	}
	enum StageState_ {
		TOP,
		BOTTOM
	};

	// --- ゲーム設定 ---
	StageState_ stageState = TOP;	// 現在のステージ状態
	bool isRotate = false;			// カメラ回転中かどうか

private:
	GameConfig() = default;

};