#pragma once

enum class EasingType {
	// Quad
	EASING_EASE_IN_QUAD,
	EASING_EASE_OUT_QUAD,
	EASING_EASE_IN_OUT_QUAD,
	// Cubic
	EASING_EASE_IN_CUBIC,
	EASING_EASE_OUT_CUBIC,
	EASING_EASE_IN_OUT_CUBIC,
	// Quart
	EASING_EASE_IN_QUART,
	EASING_EASE_OUT_QUART,
	EASING_EASE_IN_OUT_QUART,
	// Quint
	EASING_EASE_IN_QUINT,
	EASING_EASE_OUT_QUINT,
	EASING_EASE_IN_OUT_QUINT,
	// Sine
	EASING_EASE_IN_SINE,
	EASING_EASE_OUT_SINE,
	EASING_EASE_IN_OUT_SINE,
	// Expo
	EASING_EASE_IN_EXPO,
	EASING_EASE_OUT_EXPO,
	EASING_EASE_IN_OUT_EXPO,
	// Circ
	EASING_EASE_IN_CIRC,
	EASING_EASE_OUT_CIRC,
	EASING_EASE_IN_OUT_CIRC,
	// Back
	EASING_EASE_IN_BACK,
	EASING_EASE_OUT_BACK,
	EASING_EASE_IN_OUT_BACK,
	// Elastic
	EASING_EASE_IN_ELASTIC,
	EASING_EASE_OUT_ELASTIC,
	EASING_EASE_IN_OUT_ELASTIC,
	// Bounce
	EASING_EASE_OUT_BOUNCE,
	EASING_EASE_IN_BOUNCE,
	EASING_EASE_IN_OUT_BOUNCE
};

class Easing {
public:



	float start_;
	float end_;
	float easingRate;
	EasingType typeIndex = EasingType::EASING_EASE_IN_QUAD;
	bool isMove;
	float time_;
	float speed_;

	Easing();
	void Init(const float& start, const float& end, const int& frame, EasingType type);
	void Update();
	void Start();
	void Reset();

	float lerp(float start, float end, float t);

	// Quad
	float easeInQuad(float x);
	float easeOutQuad(float x);
	float easeInOutQuad(float x);

	// Cubic
	float easeInCubic(float x);
	float easeOutCubic(float x);
	float easeInOutCubic(float x);

	// Quart
	float easeInQuart(float x);
	float easeOutQuart(float x);
	float easeInOutQuart(float x);

	// Quint
	float easeInQuint(float x);
	float easeOutQuint(float x);
	float easeInOutQuint(float x);

	// Sine
	float easeInSine(float x);
	float easeOutSine(float x);
	float easeInOutSine(float x);

	// Expo
	float easeInExpo(float x);
	float easeOutExpo(float x);
	float easeInOutExpo(float x);

	// Circ
	float easeInCirc(float x);
	float easeOutCirc(float x);
	float easeInOutCirc(float x);

	// Back
	float easeInBack(float x);
	float easeOutBack(float x);
	float easeInOutBack(float x);

	// Elastic
	float easeInElastic(float x);
	float easeOutElastic(float x);
	float easeInOutElastic(float x);

	// Bounce
	float easeOutBounce(float x);
	float easeInBounce(float x);
	float easeInOutBounce(float x);
};