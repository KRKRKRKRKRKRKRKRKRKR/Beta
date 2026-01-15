#pragma once
#include "Object2D.h"
#include "Easing.h"
#include <Novice.h>

class Stage {
public:
	Stage();
	void Draw();

private:
	//ステージのデータ
	struct StageData {
		Transform2D transform_;		//ステージの情報
	};

	float stageWidth_ = 500.0f;
	float stageHeight_ = 500.0f;
	StageData stageData_;
	int stageTextureHandle_ = Novice::LoadTexture("./BOX.png");
};