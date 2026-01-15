#pragma once
#include "Object2D.h"
#include "Camera2D.h"
#include "GameConfig.h"
#include <Novice.h>

class Player {
public:
	void Init();
	void Update(char* keys, char* preKeys);
	void Draw();
	void SetHitStage(const bool& hit) { isHitStage = hit; }

	Transform2D transform;										//データ
private:
	enum Direction {
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	bool canChangeDirection;									//方向を変えることができるか
	int directionLeft;											//方向変更残り回数
	int hp;														//体力
	Vector2 velocity = {};										//速度
	Direction direction;										//向いている方向
	float walkSpeed = 5.0f;										//歩く速さ
	float gravity = 0.98f;										//重力
	bool isHitStage = false;									//ステージに当たったか
	int playerTextureHandle = Novice::LoadTexture("./BOX.png");	//テクスチャハンドル

	void Move(char* keys, char* preKeys);

};