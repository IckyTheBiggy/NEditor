#pragma once

#include <iostream>

enum class Easing
{
	None,
	SineIn,
	SineOut,
	SineInOut,
	QuadIn,
	QuadOut,
	QuadInOut,
	CubicIn,
	CubicOut,
	CubicInOut,
	QuartIn,
	QuartOut,
	QuartInOut,
	QuintIn,
	QuintOut,
	QuintInOut,
	ExpoIn,
	ExpoOut,
	ExpoInOut,
	CircIn,
	CircOut,
	CircInOut,
	BackIn,
	BackOut,
	BackInOut,
	ElasticIn,
	ElasticOut,
	ElasticInOut,
	BounceIn,
	BounceOut,
	BounceInOut
};

class Lerping
{
  public:
	static float Lerp(float a, float b, float t);
	static float LerpPos(float &lerpPos, float delta, Easing easing);
	static float Ease(float t, Easing easing);

	static float SineIn(float t);
	static float SineOut(float t);
	static float SineInOut(float t);

	static float QuadIn(float t);
	static float QuadOut(float t);
	static float QuadInOut(float t);

	static float CubicIn(float t);
	static float CubicOut(float t);
	static float CubicInOut(float t);

	static float QuartIn(float t);
	static float QuartOut(float t);
	static float QuartInOut(float t);

	static float QuintIn(float t);
	static float QuintOut(float t);
	static float QuintInOut(float t);

	static float ExpoIn(float t);
	static float ExpoOut(float t);
	static float ExpoInOut(float t);

	static float CircIn(float t);
	static float CircOut(float t);
	static float CircInOut(float t);

	static float BackIn(float t);
	static float BackOut(float t);
	static float BackInOut(float t);

	static float ElasticIn(float t);
	static float ElasticOut(float t);
	static float ElasticInOut(float t);

	static float BounceIn(float t);
	static float BounceOut(float t);
	static float BounceInOut(float t);
};