#pragma once
#include "Scene.h"

class CreditScene : public Scene
{
public:
	CreditScene(SceneManager* manager);
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	SceneManager* sceneManager;

	int bgTexture_;
	int enterTexture_;           // <-- Add handle for enter image

	int posX_ = 640;
	int posY_ = 360;
	int width_ = 1280;
	int height_ = 720;

	int enterX_ = 600;           // <-- Adjust these to position under "Program:"
	int enterY_ = 620;
	int enterW_ = 78;            // <-- Adjust size to fit the scene (original PNG is 64x58, see below for scaling)
	int enterH_ = 86;

	int frameCount_ = 0;         // <- For hover animation
	float hoverOffset_ = 0.0f;
};