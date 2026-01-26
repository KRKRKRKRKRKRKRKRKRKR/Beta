#include "CreditScene.h"
#include <Novice.h>
#include <cmath>
#include "Easing.h"

CreditScene::CreditScene(SceneManager* manager)
	: sceneManager(manager)
{
	bgTexture_ = Novice::LoadTexture("./Textures/UI/BackGround/credit.png");
	enterTexture_ = Novice::LoadTexture("./Textures/UI/enter.png");
}

void CreditScene::Update(char* keys, char* preKeys)
{
	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN])
	{
		sceneManager->ChangeScene(SceneType::Title);
	}
	frameCount_++;

	// In CreditScene.cpp, Update()
	bgBreathPhase_ += bgBreathSpeed_;
	//bgColorPhase_ += bgColorSpeed_;

	hoverOffset_ = std::sinf(frameCount_ * 0.04f) * 13.0f; // Same as in TitleLogo
}

void CreditScene::Draw()
{
    // Calculate breathing scale and color tint for the background
    float breathScale = 1.0f + std::sin(bgBreathPhase_) * 0.012f;
    //int brightness = 200 + static_cast<int>(std::sin(bgColorPhase_) * 28);
    //unsigned int tint = 0xFF000000 | (brightness << 16) | (brightness << 8) | brightness;

    // Draw animated background

    Novice::DrawBox(0,0,
        1280, 720,
        0.0f,
        BLACK,
        kFillModeSolid
	);

    Novice::DrawSprite(
        posX_ - static_cast<int>((width_ * breathScale) / 2),
        posY_ - static_cast<int>((height_ * breathScale) / 2),
        bgTexture_,
        breathScale, breathScale,
        0.0f,
        WHITE
    );

    // Enter key animation (remains as before)
    float scale = 1.0f;
    Novice::DrawSprite(
        enterX_,
        enterY_ + static_cast<int>(hoverOffset_),
        enterTexture_,
        scale, scale,
        0.0f,
        WHITE
    );
}