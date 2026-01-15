#include "Player.h"

void Player::Init() {
	transform.Init({ 640.0f,360.0f }, 50.0f, 50.0f);
	onGround = false;
	canChangeDirection = true;
	directionLeft = 1;
	hp = 3;
}

void Player::Update(char* keys, char* preKeys, const StageState_& stageState) {
	Move(keys, preKeys, stageState);
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

void Player::Move(char* keys, char* preKeys, const StageState_& stageState) {
	switch (stageState) {
	case TOP:
		if (keys[DIK_W] && preKeys[DIK_W]) {
			transform.worldPos.y += 5.0f;
		}
		if (keys[DIK_S]) {
			transform.worldPos.y -= 5.0f;
		}
		if (keys[DIK_A]) {
			transform.worldPos.x -= 5.0f;
		}
		if (keys[DIK_D]) {
			transform.worldPos.x += 5.0f;
		}
		break;

	case BOTTOM:
		if (keys[DIK_W]) {
			transform.worldPos.y -= 5.0f;
		}
		if (keys[DIK_S]) {
			transform.worldPos.y += 5.0f;
		}
		if (keys[DIK_A]) {
			transform.worldPos.x += 5.0f;
		}
		if (keys[DIK_D]) {
			transform.worldPos.x -= 5.0f;
		}
		break;
	}
}

