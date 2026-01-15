#pragma once
#include "Object2D.h"
#include "Camera2D.h"
#include "Config.h"
#include <Novice.h>

class Player {
public:
	void Init();
	void Update(char * keys,char * preKeys,const StageState_ &stageState);
	void Draw();

private:
	Transform2D transform;										//データ
	bool onGround;												//地面についたか
	bool canChangeDirection;									//方向を変えることができるか
	int directionLeft;											//方向変更残り回数
	int hp;														//体力
	int playerTextureHandle = Novice::LoadTexture("./BOX.png");//テクスチャハンドル
	
	//移動処理
	void Move(char * keys,char * preKeys,const StageState_ &stageState);

};