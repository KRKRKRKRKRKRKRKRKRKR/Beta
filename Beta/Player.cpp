#include "Player.h"

void Player::Init() {
	transform.Init({ 640.0f,360.0f }, 50.0f, 50.0f);
	isHitStage = false;
	canChangeGravity = true;
	onGround = false;
	directionChangeLeft = maxDirectionChange;
	hp = 3;
}

void Player::Update(char* keys, char* preKeys, const Transform2D& stage) {
	Move(keys, preKeys, stage);
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

void Player::Move(char* keys, char* preKeys, const Transform2D& stage) {

	if (GameConfig::GetInstance()->GetIsRotate()) {
		return;
	}

	//GetIsRotate == false	ステージが回転していない
	//OnGround == true		地面にいる

	if (onGround) {
		onGround = false;
		canChangeGravity = true;
		if (gravity.x == 0.0f && gravity.y == 0.0f) {
			switch (GameConfig::GetInstance()->GetStageState()) {
			case GameConfig::TOP:

				gravity = { 0.0f,gravityStrength };
				break;
			case GameConfig::BOTTOM:

				gravity = { 0.0f,-gravityStrength };
				break;
			case GameConfig::LEFT:
				gravity = { -gravityStrength,0.0f };
				break;
			case GameConfig::RIGHT:

				gravity = { gravityStrength,0.0f };
				break;

			}
		}
	}

	//GetIsRotate == false	ステージが回転していない
	//OnGround == false		空中にいる
	//canChangeGravity		重力変更可能

	if (!onGround && canChangeGravity) {
		switch (GameConfig::GetInstance()->GetStageState()) {
			//--------------------------------------------------------------------------
		case GameConfig::TOP:
			if (keys[DIK_W] && !preKeys[DIK_W]) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,gravityStrength };
				directionChangeLeft--;
			}
			if (keys[DIK_S] && !preKeys[DIK_S]) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,-gravityStrength };
				directionChangeLeft--;
			}
			if (keys[DIK_A] && !preKeys[DIK_A]) {
				velocity = { 0.0f,0.0f };
				gravity = { -gravityStrength,0.0f };
				directionChangeLeft--;
			}
			if (keys[DIK_D] && !preKeys[DIK_D]) {
				velocity = { 0.0f,0.0f };
				gravity = { gravityStrength,0.0f };
				directionChangeLeft--;
			}
			break;

			//----------------------------------------------------------------------
		case GameConfig::BOTTOM:
			if (keys[DIK_W] && !preKeys[DIK_W]) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,-gravityStrength };
				directionChangeLeft--;
			}
			if (keys[DIK_S] && !preKeys[DIK_S]) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,gravityStrength };
				directionChangeLeft--;
			}
			if (keys[DIK_A] && !preKeys[DIK_A]) {
				velocity = { 0.0f,0.0f };
				gravity = { gravityStrength,0.0f };
				directionChangeLeft--;
			}
			if (keys[DIK_D] && !preKeys[DIK_D]) {
				velocity = { 0.0f,0.0f };
				gravity = { -gravityStrength,0.0f };
				directionChangeLeft--;
			}
			break;
			//----------------------------------------------------------------------
		case GameConfig::LEFT:
			if (keys[DIK_W] && !preKeys[DIK_W]) {
				velocity = { 0.0f,0.0f };
				gravity = { -gravityStrength,0.0f };
				directionChangeLeft--;
			}
			if (keys[DIK_S] && !preKeys[DIK_S]) {
				velocity = { 0.0f,0.0f };
				gravity = { gravityStrength,0.0f };
				directionChangeLeft--;
			}
			if (keys[DIK_A] && !preKeys[DIK_A]) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,-gravityStrength };
				directionChangeLeft--;
			}
			if (keys[DIK_D] && !preKeys[DIK_D]) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,gravityStrength };
				directionChangeLeft--;
			}
			break;
			//------------------------------------------------------------------
		case GameConfig::RIGHT:
			if (keys[DIK_W] && !preKeys[DIK_W]) {
				velocity = { 0.0f,0.0f };
				gravity = { gravityStrength,0.0f };
				directionChangeLeft--;
			}
			if (keys[DIK_S] && !preKeys[DIK_S]) {
				velocity = { 0.0f,0.0f };
				gravity = { -gravityStrength,0.0f };
				directionChangeLeft--;
			}
			if (keys[DIK_A] && !preKeys[DIK_A]) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,gravityStrength };
				directionChangeLeft--;
			}
			if (keys[DIK_D] && !preKeys[DIK_D]) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,-gravityStrength };
				directionChangeLeft--;
			}
			break;
		}

		//方向変更回数が0になったら重力変更不可
		if (directionChangeLeft == 0) {
			canChangeGravity = false;
		}
	}


	//重力を加算
	velocity.x += gravity.x;
	velocity.y += gravity.y;

	transform.worldPos.x += velocity.x;
	transform.worldPos.y += velocity.y;

	onGround = false;

	//当たり判定
	isHitLeft = collider.IsHitLeft(transform, stage);
	isHitRight = collider.IsHitRight(transform, stage);
	isHitTop = collider.IsHitTop(transform, stage);
	isHitBottom = collider.IsHitBottom(transform, stage);

	if (gravity.x < 0 && isHitLeft) {
		onGround = true;
		GameConfig::GetInstance()->SetStageState(GameConfig::LEFT);
	}
	if (gravity.x > 0 && isHitRight) {
		onGround = true;
		GameConfig::GetInstance()->SetStageState(GameConfig::RIGHT);
	}
	if (gravity.y < 0 && isHitBottom) {
		onGround = true;
		GameConfig::GetInstance()->SetStageState(GameConfig::BOTTOM);
	}
	if (gravity.y > 0 && isHitTop) {
		onGround = true;
		GameConfig::GetInstance()->SetStageState(GameConfig::TOP);
	}

	//地面にいるか判定
	if (onGround) {
		velocity = { 0.0f,0.0f };
		directionChangeLeft = maxDirectionChange;
	}

	Novice::ScreenPrintf(0, 30, "Player Pos X: %.2f Y: %.2f", transform.worldPos.x, transform.worldPos.y);
	Novice::ScreenPrintf(0, 50, "Player OnGround = %s", (onGround == true ? "True" : "false"));
	Novice::ScreenPrintf(0, 70, "Gravity X: %.2f Y: %.2f", gravity.x, gravity.y);
	Novice::ScreenPrintf(0, 90, "Velocity X: %.2f Y: %.2f", velocity.x, velocity.y);
	Novice::ScreenPrintf(0, 110, "DirectionChangeLeft: %d", directionChangeLeft);
	//回転しているか
	Novice::ScreenPrintf(0, 130, "IsRotate: %s", (GameConfig::GetInstance()->GetIsRotate() == true ? "true" : "false"));

	//top
	Novice::ScreenPrintf(0, 150, "isHitTop: %s", (isHitTop == true ? "True" : "false"));
	//bottom
	Novice::ScreenPrintf(0, 170, "isHitBottom: %s", (isHitBottom == true ? "True" : "false"));
	//left
	Novice::ScreenPrintf(0, 190, "isHitLeft: %s", (isHitLeft == true ? "True" : "false"));
	//right
	Novice::ScreenPrintf(0, 210, "isHitRight: %s", (isHitRight == true ? "True" : "false"));

	Novice::ScreenPrintf(0, 230, "StageState: %d", GameConfig::GetInstance()->GetStageState());
	Novice::ScreenPrintf(0, 250, "0 = L,		1 = R,		2 = T,		B = 3");
	Novice::ScreenPrintf(0, 270, "");
}
