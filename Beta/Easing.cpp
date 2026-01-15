#define _USE_MATH_DEFINES
#include <math.h>
#include "Easing.h"

Easing::Easing() {
	start_ = 0.0f;
	end_ =  0.0f;
	easingRate = 0.0f;
	time_ = 0.0f;
	speed_ = 0.0f;
	typeIndex = EasingType::EASING_EASE_IN_QUAD;
	isMove = false;
}

void Easing::Init(const float& start, const float& end, const int& frame, EasingType type) {
	start_ = start;
	end_ = end;
	easingRate = start;
	time_ = 0.0f;
	speed_ = 1.0f / frame;
	typeIndex = type;
	isMove = false;
}

void Easing::Start() {
	easingRate = start_;
	isMove = true;
}

void Easing::Reset() {
	easingRate = start_;
	time_ = 0.0f;
	isMove = false;
}

void Easing::Update() {
	if (isMove) {
		time_ += speed_;
		if (time_ >= 1.0f) {
			time_ = 1.0f;
			isMove = false;
		}
		float t = 0.0f;
		switch (typeIndex) {
			// Quad
		case EasingType::EASING_EASE_IN_QUAD:
			t = easeInQuad(time_);
			break;
		case EasingType::EASING_EASE_OUT_QUAD:
			t = easeOutQuad(time_);
			break;
		case EasingType::EASING_EASE_IN_OUT_QUAD:
			t = easeInOutQuad(time_);
			break;
			// Cubic
		case EasingType::EASING_EASE_IN_CUBIC:
			t = easeInCubic(time_);
			break;
		case EasingType::EASING_EASE_OUT_CUBIC:
			t = easeOutCubic(time_);
			break;
		case EasingType::EASING_EASE_IN_OUT_CUBIC:
			t = easeInOutCubic(time_);
			break;
			// Quart
		case EasingType::EASING_EASE_IN_QUART:
			t = easeInQuart(time_);
			break;
		case EasingType::EASING_EASE_OUT_QUART:
			t = easeOutQuart(time_);
			break;
		case EasingType::EASING_EASE_IN_OUT_QUART:
			t = easeInOutQuart(time_);
			break;
			// Quint
		case EasingType::EASING_EASE_IN_QUINT:
			t = easeInQuint(time_);
			break;
		case EasingType::EASING_EASE_OUT_QUINT:
			t = easeOutQuint(time_);
			break;
		case EasingType::EASING_EASE_IN_OUT_QUINT:
			t = easeInOutQuint(time_);
			break;
			// Sine
		case EasingType::EASING_EASE_IN_SINE:
			t = easeInSine(time_);
			break;
		case EasingType::EASING_EASE_OUT_SINE:
			t = easeOutSine(time_);
			break;
		case EasingType::EASING_EASE_IN_OUT_SINE:
			t = easeInOutSine(time_);
			break;
			// Expo
		case EasingType::EASING_EASE_IN_EXPO:
			t = easeInExpo(time_);
			break;
		case EasingType::EASING_EASE_OUT_EXPO:
			t = easeOutExpo(time_);
			break;
		case EasingType::EASING_EASE_IN_OUT_EXPO:
			t = easeInOutExpo(time_);
			break;
			// Circ
		case EasingType::EASING_EASE_IN_CIRC:
			t = easeInCirc(time_);
			break;
		case EasingType::EASING_EASE_OUT_CIRC:
			t = easeOutCirc(time_);
			break;
		case EasingType::EASING_EASE_IN_OUT_CIRC:
			t = easeInOutCirc(time_);
			break;
			// Back
		case EasingType::EASING_EASE_IN_BACK:
			t = easeInBack(time_);
			break;
		case EasingType::EASING_EASE_OUT_BACK:
			t = easeOutBack(time_);
			break;
		case EasingType::EASING_EASE_IN_OUT_BACK:
			t = easeInOutBack(time_);
			break;
			// Elastic
		case EasingType::EASING_EASE_IN_ELASTIC:
			t = easeInElastic(time_);
			break;
		case EasingType::EASING_EASE_OUT_ELASTIC:
			t = easeOutElastic(time_);
			break;
		case EasingType::EASING_EASE_IN_OUT_ELASTIC:
			t = easeInOutElastic(time_);
			break;
			// Bounce
		case EasingType::EASING_EASE_OUT_BOUNCE:
			t = easeOutBounce(time_);
			break;
		case EasingType::EASING_EASE_IN_BOUNCE:
			t = easeInBounce(time_);
			break;
		case EasingType::EASING_EASE_IN_OUT_BOUNCE:
			t = easeInOutBounce(time_);
			break;
		}
		easingRate = lerp(start_, end_, t);
	}
}

float Easing::lerp(float start, float end, float t) {
	return start + (end - start) * t;
}

// Quad
float Easing::easeInQuad(float x) {
	return x * x;
}

float Easing::easeOutQuad(float x) {
	return 1 - (1 - x) * (1 - x);
}

float Easing::easeInOutQuad(float x) {
	return x < 0.5f ? 2 * x * x : 1 - powf(-2 * x + 2, 2) / 2;
}

// Cubic
float Easing::easeInCubic(float x) {
	return x * x * x;
}

float Easing::easeOutCubic(float x) {
	return 1 - powf(1 - x, 3);
}

float Easing::easeInOutCubic(float x) {
	return x < 0.5f ? 4 * x * x * x : 1 - powf(-2 * x + 2, 3) / 2;
}

// Quart
float Easing::easeInQuart(float x) {
	return x * x * x * x;
}

float Easing::easeOutQuart(float x) {
	return 1 - powf(1 - x, 4);
}

float Easing::easeInOutQuart(float x) {
	return x < 0.5f ? 8 * x * x * x * x : 1 - powf(-2 * x + 2, 4) / 2;
}

// Quint
float Easing::easeInQuint(float x) {
	return x * x * x * x * x;
}

float Easing::easeOutQuint(float x) {
	return 1 - powf(1 - x, 5);
}

float Easing::easeInOutQuint(float x) {
	return x < 0.5f ? 16 * x * x * x * x * x : 1 - powf(-2 * x + 2, 5) / 2;
}

// Sine
float Easing::easeInSine(float x) {
	return 1 - cosf((x * static_cast<float>(M_PI)) / 2);
}

float Easing::easeOutSine(float x) {
	return sinf((x * static_cast<float>(M_PI)) / 2);
}

float Easing::easeInOutSine(float x) {
	return -(cosf(static_cast<float>(M_PI) * x) - 1) / 2;
}

// Expo
float Easing::easeInExpo(float x) {
	return x == 0 ? 0 : powf(2, 10 * x - 10);
}

float Easing::easeOutExpo(float x) {
	return x == 1 ? 1 : 1 - powf(2, -10 * x);
}

float Easing::easeInOutExpo(float x) {
	return x == 0 ? 0 : x == 1 ? 1 : x < 0.5f ? powf(2, 20 * x - 10) / 2 : (2 - powf(2, -20 * x + 10)) / 2;
}

// Circ
float Easing::easeInCirc(float x) {
	return 1 - sqrtf(1 - powf(x, 2));
}

float Easing::easeOutCirc(float x) {
	return sqrtf(1 - powf(x - 1, 2));
}

float Easing::easeInOutCirc(float x) {
	return x < 0.5f ? (1 - sqrtf(1 - powf(2 * x, 2))) / 2 : (sqrtf(1 - powf(-2 * x + 2, 2)) + 1) / 2;
}

// Back
float Easing::easeInBack(float x) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;
	return c3 * x * x * x - c1 * x * x;
}

float Easing::easeOutBack(float x) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;
	return 1 + c3 * powf(x - 1, 3) + c1 * powf(x - 1, 2);
}

float Easing::easeInOutBack(float x) {
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;
	return x < 0.5f ? (powf(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
		: (powf(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
}

// Elastic
float Easing::easeInElastic(float x) {
	const float c4 = (2 * static_cast<float>(M_PI)) / 3;
	return x == 0 ? 0 : x == 1 ? 1 : -powf(2, 10 * x - 10) * sinf((x * 10 - 10.75f) * c4);
}

float Easing::easeOutElastic(float x) {
	const float c4 = (2 * static_cast<float>(M_PI)) / 3;
	return x == 0 ? 0 : x == 1 ? 1 : powf(2, -10 * x) * sinf((x * 10 - 0.75f) * c4) + 1;
}

float Easing::easeInOutElastic(float x) {
	const float c5 = (2 * static_cast<float>(M_PI)) / 4.5f;
	return x == 0 ? 0 : x == 1 ? 1 : x < 0.5f ?
		-(powf(2, 20 * x - 10) * sinf((20 * x - 11.125f) * c5)) / 2 :
		(powf(2, -20 * x + 10) * sinf((20 * x - 11.125f) * c5)) / 2 + 1;
}

// Bounce
float Easing::easeOutBounce(float x) {
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		x -= 1.5f / d1;
		return n1 * x * x + 0.75f;
	}
	else if (x < 2.5 / d1) {
		x -= 2.25f / d1;
		return n1 * x * x + 0.9375f;
	}
	else {
		x -= 2.625f / d1;
		return n1 * x * x + 0.984375f;
	}
}

float Easing::easeInBounce(float x) {
	return 1 - easeOutBounce(1 - x);
}

float Easing::easeInOutBounce(float x) {
	return x < 0.5f ? (1 - easeOutBounce(1 - 2 * x)) / 2 : (1 + easeOutBounce(2 * x - 1)) / 2;
}
