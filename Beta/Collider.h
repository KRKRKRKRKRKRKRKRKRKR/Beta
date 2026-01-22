#pragma once
#include "Object2D.h"

class Collider {
public:
	//矩形同士の当たり判定
	bool AABB(const Transform2D& obj1, const Transform2D& obj2);

	//点と矩形の当たり判定
	bool IsHitPoint(const Vector2 point, const Transform2D& obj);

	//矩形の中の当たり判定
	bool ClampX(Transform2D& obj, const Transform2D& stage);

	//矩形の中の当たり判定
	bool ClampY(Transform2D& obj, const Transform2D& stage);

	bool IsHitLeft(Transform2D& obj, const Transform2D& stage);
	bool IsHitRight(Transform2D& obj, const Transform2D& stage);
	bool IsHitTop(Transform2D& obj, const Transform2D& stage);
	bool IsHitBottom(Transform2D& obj, const Transform2D& stage);
};