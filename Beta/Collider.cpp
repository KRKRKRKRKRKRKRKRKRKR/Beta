#include "Collider.h"

bool Collider::AABB(const Transform2D& obj1, const Transform2D& obj2) {
	float left1 = obj1.worldPos.x - obj1.width / 2.0f;
	float right1 = obj1.worldPos.x + obj1.width / 2.0f;
	float top1 = obj1.worldPos.y + obj1.height / 2.0f;
	float bottom1 = obj1.worldPos.y - obj1.height / 2.0f;
	float left2 = obj2.worldPos.x - obj2.width / 2.0f;
	float right2 = obj2.worldPos.x + obj2.width / 2.0f;
	float top2 = obj2.worldPos.y + obj2.height / 2.0f;
	float bottom2 = obj2.worldPos.y - obj2.height / 2.0f;
	if (right1 < left2 || left1 > right2 || top1 < bottom2 || bottom1 > top2) {
		return false;
	}
	return true;
}

bool Collider::Clamp(Transform2D& obj, const Transform2D& stage) {
	bool isHitWall = false;

	float stageLeft = stage.worldPos.x - stage.width / 2.0f;
	float stageRight = stage.worldPos.x + stage.width / 2.0f;
	float stageTop = stage.worldPos.y + stage.height / 2.0f;
	float stageBottom = stage.worldPos.y - stage.height / 2.0f;

	float objLeft = obj.worldPos.x - obj.width / 2.0f;
	float objRight = obj.worldPos.x + obj.width / 2.0f;
	float objTop = obj.worldPos.y + obj.height / 2.0f;
	float objBottom = obj.worldPos.y - obj.height / 2.0f;

	if (objLeft < stageLeft) {
		obj.worldPos.x = stageLeft + obj.width / 2.0f;
		isHitWall = true;
	}
	else if (objRight > stageRight) {
		obj.worldPos.x = stageRight - obj.width / 2.0f;
		isHitWall = true;
	}

	if (objTop > stageTop) {
		obj.worldPos.y = stageTop - obj.height / 2.0f;
		isHitWall = true;
	}
	else if (objBottom < stageBottom) {
		obj.worldPos.y = stageBottom + obj.height / 2.0f;
		isHitWall = true;
	}

	return isHitWall;
}