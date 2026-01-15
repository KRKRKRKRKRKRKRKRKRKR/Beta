#include "Stage.h"
#include <Novice.h>
#include "Camera2D.h"

Stage::Stage() {
	stageData_.transform_.Init({ 640.0f,360.0f }, stageWidth_, stageHeight_);
}

void Stage::Draw() {
	Quad screen = Camera2D::GetInstance()->WorldToScreen(stageData_.transform_);
	Novice::DrawQuad(
		static_cast<int>(screen.v[0].x), static_cast<int>(screen.v[0].y),
		static_cast<int>(screen.v[1].x), static_cast<int>(screen.v[1].y),
		static_cast<int>(screen.v[2].x), static_cast<int>(screen.v[2].y),
		static_cast<int>(screen.v[3].x), static_cast<int>(screen.v[3].y),
		0, 0,
		static_cast<int>(stageData_.transform_.width),
		static_cast<int>(stageData_.transform_.height),
		stageTextureHandle_,WHITE
	);
}