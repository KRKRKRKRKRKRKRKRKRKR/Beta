#pragma once
#include <Novice.h>
#include "Object2D.h"
#include "Camera2D.h"
#include "GameConfig.h"
#include"Collider.h"
#include "Easing.h"
#include <vector>
class Enemy{
public:
	Enemy();
	Enemy(const Transform2D & spawnStage);
	void Init(const Transform2D & spawnStage);
	void Update();
	void Draw();
private:

	//敵データ構造体
	struct EnemyData {
		Transform2D transform;				//データ
		Vector2 size = { 68.0f,68.0f };		//サイズ
		Collider collider;					//当たり判定
		Vector2 velocity = {};				//速度
		int count;							//カウント
		Vector2 speed;						//移動速度
		bool isActive;						//生存フラグ
	};

	//敵データ配列
	std::vector<EnemyData> enemies;
	
	const int maxEnemiesSpawnCount = 10;	//最大敵数
	//敵テクスチャ
	int count1Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy1.png");
	int count2Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy2.png");
	int count3Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy3.png");
	int count4Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy4.png");
	int count5Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy5.png");
	int count6Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy6.png");

	//敵スポーン処理
	void SpawnEnemy(const Transform2D & spawnStage);
	float GetRandom(float min, float max);
};

