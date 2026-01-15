#pragma once
#include "Object2D.h"

class Collider {
public:
	//矩形同士の当たり判定
	 bool AABB(const Transform2D& obj1, const Transform2D& obj2);

	//矩形の中の当たり判定
	bool Clamp(Transform2D & obj,const Transform2D & stage);
};