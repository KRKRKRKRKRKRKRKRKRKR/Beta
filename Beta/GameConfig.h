#pragma once

class GameConfig {
public:
	static GameConfig* GetInstance() {
		static GameConfig instance;
		return &instance;
	}

	enum StageState_ {
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	StageState_ GetStageState() const { return stageState; }
	StageState_ GetPrevStageState() const { return prevStageState; }
	bool GetIsRotate() const { return isRotate; }

	void SetStageState(StageState_ state) { stageState = state; }
	void SetIsRotate(bool rotate) { isRotate = rotate; }
	void SetPrevStageState(StageState_ state) { prevStageState = state; }


	int GetCurrentStage()const { return currentStage; }
	void SetCurrentStage(int stage) { currentStage = stage; }
	void NextStage() { currentStage++; }

	bool GetIsFinishedStage() const { return isFinishedStage; }
	void SetIsFinishedStage(bool finished) { isFinishedStage = finished; }

	int GetCurrentWave() const { return currentWave; }
	int SetCurrentWave(int wave) { currentWave = wave; }

	float GetTimeScale() const { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }

private:
	GameConfig() = default;
	StageState_ stageState = TOP;
	StageState_ prevStageState = TOP;
	bool isRotate = false;				//カメラ回転中かどうか
	int currentStage = 0;				//現在のステージ数
	bool isFinishedStage = false;		//ステージクリアフラグ
	int currentWave = 0;				//現在のウェーブ数
	
	float timeScale = 1.0f;              //時間倍率
	

};