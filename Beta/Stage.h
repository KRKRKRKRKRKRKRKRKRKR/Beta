#pragma once
#include "Object2D.h"
#include "Easing.h"
#include <Novice.h>

class Stage {
public:
	Stage();
	void Draw();
	Transform2D& GetTransform() { return transform_; }
private:
	
	float stageWidth_ = 500.0f;
	float stageHeight_ = 500.0f;
	Transform2D transform_;
	int stageTextureHandle_ = Novice::LoadTexture("./BOX.png");
};