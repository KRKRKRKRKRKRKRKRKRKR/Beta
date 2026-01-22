#pragma once
#include "Sence.h"

class RankingScene : public Sence
{
public:
	RankingScene(SceneManager* manager);
	void Update() override;
	void Draw() override;

private:
	SceneManager* sceneManager;
};

