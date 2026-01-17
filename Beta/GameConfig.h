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

private:
	GameConfig() = default;
	StageState_ stageState = TOP;
	StageState_ prevStageState = TOP;
	bool isRotate = false;
};