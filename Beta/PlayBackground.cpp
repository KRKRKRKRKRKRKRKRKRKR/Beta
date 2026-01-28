#include "PlayBackground.h"
#include <Novice.h>

PlayBackground::PlayBackground()
{
	textureHandles_[0] = Novice::LoadTexture("./Textures/UI/background/bg1.png");
	textureHandles_[1] = Novice::LoadTexture("./Textures/UI/background/bg2.png");
	textureHandles_[2] = Novice::LoadTexture("./Textures/UI/background/bg3.png");
	textureHandles_[3] = Novice::LoadTexture("./Textures/UI/background/bg4.png");
	textureHandles_[4] = Novice::LoadTexture("./Textures/UI/background/bg5.png");
}

void PlayBackground::Update()
{
	frameCounter_++;
	if (frameCounter_ >= frameChangeInterval_) {
		frameCounter_ = 0;
		currentFrame_++;
		if (currentFrame_ >= kFrameCount) {
			currentFrame_ = 0;
		}
	}
}

void PlayBackground::Draw()
{
	int handle = textureHandles_[currentFrame_];
	Novice::DrawSprite(
		posX_ - width_ /2,
		posY_ - height_ /2,
		handle,
		1.0f, 1.0f,
		0.0f,
		WHITE);
}