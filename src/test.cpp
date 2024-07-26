#include "Lerping.h"
#include <cmath>

float Lerping::Lerp(float a, float b, float t) { return a + t * (b - a); }

float Lerping::LerpPos(float &lerpPos, float delta, Easing easing)
{
	if (lerpPos >= 1)
		return 1;
	lerpPos += delta;
	lerpPos = lerpPos > 1 ? 1 : lerpPos;
	return Ease(lerpPos, easing);
}

float Lerping::Ease(float t, Easing easing)
{
	switch (easing)
	{
	case Easing::None:
		return t;
	case Easing::SineIn:
		return Lerping::SineIn(t);
	case Easing::SineOut:
		return Lerping::SineOut(t);
	case Easing::SineInOut:
		return Lerping::SineInOut(t);
	case Easing::QuadIn:
		return Lerping::QuadIn(t);
	case Easing::QuadOut:
		return Lerping::QuadOut(t);
	case Easing::QuadInOut:
		return Lerping::QuadInOut(t);
	case Easing::CubicIn:
		return Lerping::CubicIn(t);
	case Easing::CubicOut:
		return Lerping::CubicOut(t);
	case Easing::CubicInOut:
		return Lerping::CubicInOut(t);
	case Easing::QuartIn:
		return Lerping::QuartIn(t);
	case Easing::QuartOut:
		return Lerping::QuartOut(t);
	case Easing::QuartInOut:
		return Lerping::QuartInOut(t);
	case Easing::QuintIn:
		return Lerping::QuintIn(t);
	case Easing::QuintOut:
		return Lerping::QuintOut(t);
	case Easing::QuintInOut:
		return Lerping::QuintInOut(t);
	case Easing::ExpoIn:
		return Lerping::ExpoIn(t);
	case Easing::ExpoOut:
		return Lerping::ExpoOut(t);
	case Easing::ExpoInOut:
		return Lerping::ExpoInOut(t);
	case Easing::CircIn:
		return Lerping::CircIn(t);
	case Easing::CircOut:
		return Lerping::CircOut(t);
	case Easing::CircInOut:
		return Lerping::CircInOut(t);
	case Easing::BackIn:
		return Lerping::BackIn(t);
	case Easing::BackOut:
		return Lerping::BackOut(t);
	case Easing::BackInOut:
		return Lerping::BackInOut(t);
	case Easing::ElasticIn:
		return Lerping::ElasticIn(t);
	case Easing::ElasticOut:
		return Lerping::ElasticOut(t);
	case Easing::ElasticInOut:
		return Lerping::ElasticInOut(t);
	case Easing::BounceIn:
		return Lerping::BounceIn(t);
	case Easing::BounceOut:
		return Lerping::BounceOut(t);
	case Easing::BounceInOut:
		return Lerping::BounceInOut(t);
	default:
		return t;
	}
}

float Lerping::SineIn(float t) { return 1.0f - std::cos((t * M_PI) / 2.0f); }
float Lerping::SineOut(float t) { return std::sin((t * M_PI) / 2.0f); }
float Lerping::SineInOut(float t)
{
	return -(std::cos(M_PI * t) - 1.0f) / 2.0f;
}

float Lerping::QuadIn(float t) { return t * t; }
float Lerping::QuadOut(float t) { return 1.0f - (1.0f - t) * (1.0f - t); }
float Lerping::QuadInOut(float t)
{
	return t < 0.5f ? 2.0f * t * t
	                : 1.0f - std::pow(-2.0f * t + 2.0f, 2.0f) / 2.0f;
}

float Lerping::CubicIn(float t) { return t * t * t; }
float Lerping::CubicOut(float t) { return 1.0f - std::pow(1.0f - t, 3.0f); }
float Lerping::CubicInOut(float t)
{
	return t < 0.5f ? 4.0f * t * t * t
	                : 1.0f - std::pow(-2.0f * t + 2.0f, 3.0f) / 2.0f;
}

float Lerping::QuartIn(float t) { return t * t * t * t; }
float Lerping::QuartOut(float t) { return 1.0f - std::pow(1.0f - t, 4.0f); }
float Lerping::QuartInOut(float t)
{
	return t < 0.5f ? 8.0f * t * t * t * t
	                : 1.0f - std::pow(-2.0f * t + 2.0f, 4.0f) / 2.0f;
}

float Lerping::QuintIn(float t) { return t * t * t * t * t; }
float Lerping::QuintOut(float t) { return 1.0f - std::pow(1.0f - t, 5.0f); }
float Lerping::QuintInOut(float t)
{
	return t < 0.5f ? 16.0f * t * t * t * t * t
	                : 1.0f - std::pow(-2.0f * t + 2.0f, 5.0f) / 2.0f;
}

float Lerping::ExpoIn(float t)
{
	return t == 0.0f ? 0.0f : std::pow(2.0f, 10.0f * t - 10.0f);
}
float Lerping::ExpoOut(float t)
{
	return t == 1.0f ? 1.0f : 1.0f - std::pow(2.0f, -10.0f * t);
}
float Lerping::ExpoInOut(float t)
{
	return t == 0.0f   ? 0.0f
	       : t == 1.0f ? 1.0f
	       : t < 0.5f  ? std::pow(2.0f, 20.0f * t - 10.0f) / 2.0f
	                   : (2.0f - std::pow(2.0f, -20.0f * t + 10.0f)) / 2.0f;
}

float Lerping::CircIn(float t)
{
	return 1.0f - std::sqrt(1.0f - std::pow(t, 2.0f));
}
float Lerping::CircOut(float t)
{
	return std::sqrt(1.0f - std::pow(t - 1.0f, 2.0f));
}
float Lerping::CircInOut(float t)
{
	return t < 0.5f
	           ? (1.0f - std::sqrt(1.0f - std::pow(2.0f * t, 2.0f))) / 2.0f
	           : (std::sqrt(1.0f - std::pow(-2.0f * t + 2.0f, 2.0f)) + 1.0f) /
	                 2.0f;
}

float Lerping::BackIn(float t)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;
	return c3 * t * t * t - c1 * t * t;
}
float Lerping::BackOut(float t)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;
	return 1.0f + c3 * std::pow(t - 1.0f, 3.0f) + c1 * std::pow(t - 1.0f, 2.0f);
}
float Lerping::BackInOut(float t)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;
	return t < 0.5f
	           ? (std::pow(2.0f * t, 2.0f) * ((c2 + 1.0f) * 2.0f * t - c2)) /
	                 2.0f
	           : (std::pow(2.0f * t - 2.0f, 2.0f) *
	                  ((c2 + 1.0f) * (t * 2.0f - 2.0f) + c2) +
	              2.0f) /
	                 2.0f;
}

float Lerping::ElasticIn(float t)
{
	const float c4 = (2.0f * M_PI) / 3.0f;
	return t == 0.0f   ? 0.0f
	       : t == 1.0f ? 1.0f
	                   : -std::pow(2.0f, 10.0f * t - 10.0f) *
	                         std::sin((t * 10.0f - 10.75f) * c4);
}
float Lerping::ElasticOut(float t)
{
	const float c4 = (2.0f * M_PI) / 3.0f;
	return t == 0.0f   ? 0.0f
	       : t == 1.0f ? 1.0f
	                   : std::pow(2.0f, -10.0f * t) *
	                             std::sin((t * 10.0f - 0.75f) * c4) +
	                         1.0f;
}
float Lerping::ElasticInOut(float t)
{
	const float c5 = (2.0f * M_PI) / 4.5f;
	return t == 0.0f   ? 0.0f
	       : t == 1.0f ? 1.0f
	       : t < 0.5f  ? -(std::pow(2.0f, 20.0f * t - 10.0f) *
                          std::sin((20.0f * t - 11.125f) * c5)) /
	                        2.0f
	                  : (std::pow(2.0f, -20.0f * t + 10.0f) *
	                     std::sin((20.0f * t - 11.125f) * c5)) /
	                            2.0f +
	                        1.0f;
}

float Lerping::BounceIn(float t) { return 1.0f - Lerping::BounceOut(1.0f - t); }
float Lerping::BounceOut(float t)
{
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (t < 1.0f / d1)
		return n1 * t * t;
	if (t < 2.0f / d1)
	{
		t -= 1.5f / d1;
		return n1 * t * t + 0.75f;
	}
	if (t < 2.5f / d1)
	{
		t -= 2.25f / d1;
		return n1 * t * t + 0.9375f;
	}
	t -= 2.625f / d1;
	return n1 * t * t + 0.984375f;
}
float Lerping::BounceInOut(float t)
{
	return t < 0.5f ? (1.0f - Lerping::BounceOut(1.0f - 2.0f * t)) / 2.0f
	                : (1.0f + Lerping::BounceOut(2.0f * t - 1.0f)) / 2.0f;
}
