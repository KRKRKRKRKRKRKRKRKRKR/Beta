#include "Stage.h"
#include <Novice.h>
#include "Camera2D.h"

Stage::Stage() {
	transform_.Init({ 640.0f,360.0f }, stageWidth_, stageHeight_);
	enemySpawnRangeTransform_.Init({ 640.0f,360.0f }, enemySpawnRangeWidth_, enemySpawnRangeHeight_);
}

void Stage::Draw() {
	

	Quad screen = Camera2D::GetInstance()->WorldToScreen(transform_);
	Novice::DrawQuad(
		static_cast<int>(screen.v[0].x), static_cast<int>(screen.v[0].y),
		static_cast<int>(screen.v[1].x), static_cast<int>(screen.v[1].y),
		static_cast<int>(screen.v[2].x), static_cast<int>(screen.v[2].y),
		static_cast<int>(screen.v[3].x), static_cast<int>(screen.v[3].y),
		0, 0,
		static_cast<int>(transform_.width),
		static_cast<int>(transform_.height),
		stageTextureHandle_,BLUE
	);

	Quad spawnScreen = Camera2D::GetInstance()->WorldToScreen(enemySpawnRangeTransform_);
	Novice::DrawQuad(
		static_cast<int>(spawnScreen.v[0].x), static_cast<int>(spawnScreen.v[0].y),
		static_cast<int>(spawnScreen.v[1].x), static_cast<int>(spawnScreen.v[1].y),
		static_cast<int>(spawnScreen.v[2].x), static_cast<int>(spawnScreen.v[2].y),
		static_cast<int>(spawnScreen.v[3].x), static_cast<int>(spawnScreen.v[3].y),
		0, 0,
		static_cast<int>(enemySpawnRangeTransform_.width),
		static_cast<int>(enemySpawnRangeTransform_.height),
		stageTextureHandle_, GREEN
	);

	Novice::DrawSprite(0, 0, backgroundTextureHandle_, 2, 2, 0.0f, WHITE);
}