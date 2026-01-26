#pragma once
#include "Object2D.h"
#include "CameraManager.h"
#include <Novice.h>

class UI {
public:

	UI();
	void Init();
	void Draw();

private:

	Transform2D scoreBoardTransform_;
	Vector2 position_ = { 415.0f,690.0f };
	float scoreBoardW = 150.0f;
	float scoreBoardH = 46.0f;
	int scoreBoardTextureHandle_ = Novice::LoadTexture("./Textures/UI/scoreboard.png");
};