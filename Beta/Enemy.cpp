#include "Enemy.h"
#include <random>

Enemy::Enemy() {

}

Enemy::Enemy(const Transform2D & spawnStage) {
	Init(spawnStage);
}

void Enemy::Init(const Transform2D & spawnStage) {
	SpawnEnemy(spawnStage);
}

void Enemy::Update() {

}

void Enemy::Draw() {
	for (const EnemyData& enemy : enemies) {
		if (!enemy.isActive) {
			continue;
		}
	
		Quad screen = Camera2D::GetInstance()->WorldToScreen(enemy.transform);
		Novice::DrawQuad(
			static_cast<int>(screen.v[0].x), static_cast<int>(screen.v[0].y),
			static_cast<int>(screen.v[1].x), static_cast<int>(screen.v[1].y),
			static_cast<int>(screen.v[2].x), static_cast<int>(screen.v[2].y),
			static_cast<int>(screen.v[3].x), static_cast<int>(screen.v[3].y),
			0, 0,
			static_cast<int>(enemy.transform.width),
			static_cast<int>(enemy.transform.height),
			count1Texture, WHITE
		);
	}
}

//----------------------------------------------------------
// 敵のスポーン処理
// スポーン位置はステージの範囲内からランダムに決定
// スポーン位置と敵のサイズを考慮して、スポーン時にめり込まないようにする
// 
//----------------------------------------------------------

//敵スポーン処理
void Enemy::SpawnEnemy(const Transform2D& spawnStage) {
	for (int i = 0; i < maxEnemiesSpawnCount; i++) {
		EnemyData newEnemy;

		float enemyHW = newEnemy.transform.width / 2.0f;
		float enemyHH = newEnemy.transform.height / 2.0f;
		float spawnHW = spawnStage.width / 2.0f;
		float spawnHH = spawnStage.height / 2.0f;
		float rangeX = spawnHW - enemyHW;
		float rangeY = spawnHH - enemyHH;
		float spawnX = GetRandom(-rangeX, rangeX);
		float spawnY = GetRandom(-rangeY, rangeY);

		Vector2 finalSpawnPos = { spawnStage.worldPos.x + spawnX, spawnStage.worldPos.y + spawnY };
		newEnemy.transform.Init(finalSpawnPos, newEnemy.size.x, newEnemy.size.y);
		newEnemy.isActive = true;
		enemies.push_back(newEnemy);

	}
}

float Enemy::GetRandom(float min, float max) {
	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}
