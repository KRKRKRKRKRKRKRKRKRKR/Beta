#include "Player.h"

void Player::Init() {
	transform.Init({ 640.0f,360.0f }, 50.0f, 50.0f);
	isHitStage = false;
	canChangeDirection = true;
	directionLeft = 1;
	hp = 3;
}

void Player::Update(char* keys, char* preKeys) {
	Move(keys, preKeys);
}

void Player::Draw() {
	Quad screen = Camera2D::GetInstance()->WorldToScreen(transform);
	Novice::DrawQuad(
		static_cast<int>(screen.v[0].x), static_cast<int>(screen.v[0].y),
		static_cast<int>(screen.v[1].x), static_cast<int>(screen.v[1].y),
		static_cast<int>(screen.v[2].x), static_cast<int>(screen.v[2].y),
		static_cast<int>(screen.v[3].x), static_cast<int>(screen.v[3].y),
		0, 0,
		static_cast<int>(transform.width),
		static_cast<int>(transform.height),
		playerTextureHandle, RED
	);
}

void Player::Move(char* keys, char* preKeys) {
	
	//回転していない場合の重力処理
	if (!GameConfig::GetInstance()->GetIsRotate() && !isHitStage) {
		velocity.y -= gravity;
	}
		
		
	//地面に着地している場合の処理
	if (isHitStage) {
		switch (GameConfig::GetInstance()->GetStageState()) {
		case GameConfig::TOP:
			if (keys[DIK_A] && preKeys[DIK_A]) {
				transform.worldPos.x -= walkSpeed;
			}

			if (keys[DIK_D]) {
				transform.worldPos.x += walkSpeed;
			}

			gravity = 0.98f;
			
			break;
		
		case GameConfig::BOTTOM:
			if (keys[DIK_A]) {
				transform.worldPos.x += walkSpeed;
			}

			if (keys[DIK_D]) {
				transform.worldPos.x -= walkSpeed;
			}
		
			gravity = -0.98f;

			break;
		}
	}
	transform.worldPos.x += velocity.x;
	transform.worldPos.y += velocity.y;
	Novice::ScreenPrintf(0, 30, "Player Pos X: %.2f Y: %.2f", transform.worldPos.x, transform.worldPos.y);
}

