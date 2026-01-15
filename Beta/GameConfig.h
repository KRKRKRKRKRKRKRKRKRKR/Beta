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

	StageState_ GetStageState() const { 
		return stageState; 
	}
	bool GetIsRotate() const { 
		return isRotate; 
	}

	void SetStageState(StageState_ state) { stageState = state; }
	void SetIsRotate(bool rotate) { isRotate = rotate; }
private:
	GameConfig() = default;
	StageState_ stageState = TOP;
	bool isRotate = false;
};