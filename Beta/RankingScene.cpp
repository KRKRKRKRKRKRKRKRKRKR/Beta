#include "RankingScene.h"
#include <Novice.h>
#include <cmath>

RankingScene::RankingScene(SceneManager* manager)
	: sceneManager(manager)
{
	bgTexture_ = Novice::LoadTexture("./Textures/UI/BackGround/ranking.png");
	enterTexture_ = Novice::LoadTexture("./Textures/UI/enter.png");
}

void RankingScene::Update(char* keys, char* preKeys)
{
	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN])
	{
		sceneManager->ChangeScene(SceneType::Title);
	}
	frameCount_++;
	hoverOffset_ = std::sinf(frameCount_ * 0.04f) * 13.0f; // Same as in TitleLogo
}

void RankingScene::Draw()
{
	Novice::DrawSprite(
		posX_ - width_ / 2,
		posY_ - height_ / 2,
		bgTexture_,
		1.0f, 1.0f,
		0.0f,
		WHITE);

	// Draw the Enter PNG at the circled area with hover animation
	float scale = 1.0f; // Try 0.8 to make it slightly smaller (adjust if you want)
	//int dW = static_cast<int>(enterW_ * scale);
	//int dH = static_cast<int>(enterH_ * scale);

	Novice::DrawSprite(
		enterX_, // X position
		enterY_ + static_cast<int>(hoverOffset_), // Y position with hover animation
		enterTexture_,
		scale, scale,
		0.0f,
		WHITE);
}