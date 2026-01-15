#pragma once
#include "GameConfig.h"
#include "Camera2D.h"
#include "Stage.h"
#include "Player.h"
#include "Easing.h"

class GamePlay {
public:

	GamePlay();										//コンストラクタ
	void Initialize();								//初期化
	void Update(char* keys, char* preKeys);			//更新	
	void Draw();									//描画

private:

	Stage stage_;									//ステージ
	Player player_;									//プレイヤー
	Easing cameraRotateEasing_;						//カメラ回転イージング
	float currentCameraRotation_ = 0.0f;			//現在のカメラ回転角度
	void CameraControl(char* keys, char* preKeys);	//カメラ操作

};