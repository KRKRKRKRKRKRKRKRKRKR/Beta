#pragma once
#include "Sence.h"

class TitleScene : public Sence
{
public:
	TitleScene(SceneManager* manager);

	void Update() override;
	void Draw() override;

private:
	SceneManager* sceneManager;

};
