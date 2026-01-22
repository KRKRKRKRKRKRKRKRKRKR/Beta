#pragma once
#include "Sence.h"

class CreditScene : public Sence
{
public:
	CreditScene(SceneManager* manager);
	void Update() override;
	void Draw() override;

private:
	SceneManager* sceneManager;

};
