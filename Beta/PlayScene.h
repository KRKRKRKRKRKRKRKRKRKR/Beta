#pragma once
#include "Sence.h"

class PlayScene : public Sence
{
public:
	PlayScene(SceneManager* manager);

	void Update() override;
	void Draw() override;

private:
	SceneManager* sceneManager;
};