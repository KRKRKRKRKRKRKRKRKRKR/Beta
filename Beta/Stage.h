#pragma once
#include "Object2D.h"
#include "Easing.h"
#include <Novice.h>

class Stage {
public:
	Stage();
   	void Draw();
	Transform2D& GetTransform() { return transform_; }
	Transform2D& GetEnemySpawnRangeTransform() { return enemySpawnRangeTransform_; }
private:

	float stageWidth_ = 600.0f;				//ステージ幅
	float stageHeight_ = 600.0f;			//ステージ高さ
	Transform2D transform_;					//ステージデータ

	float enemySpawnRangeWidth_ = 450.0f;	//敵スポーン範囲幅
	float enemySpawnRangeHeight_ = 450.0f;  //敵スポーン範囲高さ
	Transform2D enemySpawnRangeTransform_;  //敵スポーン範囲データ
	int stageTextureHandle_ = Novice::LoadTexture("./BOX.png");
	int backgroundTextureHandle_ = Novice::LoadTexture("./Textures/Background/back1.png");
};