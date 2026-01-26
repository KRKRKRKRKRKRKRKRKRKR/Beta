#pragma once

class Score {
private:
	int score = 0;

public:
	void AddScore(int enemyNum,int enemyCount,int comboCount) {
		score = enemyCount * 100 * (comboCount / enemyNum) + score;
	}

	int GetScore() const {
		return score;
	}

	void ResetScore() {
		score = 0;
	}
};