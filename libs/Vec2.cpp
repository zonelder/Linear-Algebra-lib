#include "Vec2.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>



template<class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
    return (v < lo) ? lo : (hi< v) ? hi : v;
}

Vec2::Vec2(float x, float y)
{
	_values[0] = x;
	_values[1] = y;
}

std::string Vec2::ToString() const noexcept
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << "( " << _values[0] << " , " << _values[1] << " )";
	return ss.str();
}

const Vec2 Vec2::Up(0, 1);

const Vec2 Vec2::Down(0, -1);

const Vec2 Vec2::Right(1, 0);

const Vec2 Vec2::Left(-1, 0);

const Vec2 Vec2::One(1, 1);

const Vec2 Vec2::Zero(0, 0);

bool  Vec2::operator==(const Vec2& other) const noexcept
{
	for (int i = 0; i < 2; ++i)
	{
		if (std::fabs(_values[i] - other._values[i]) > std::max(std::abs(_values[i]), std::abs(other._values[i]))*(float)1e-4)
		{
			return false;
		}
	}
	return true;
}


float Vec2::GetX() const noexcept
{
	return _values[0];
}

float Vec2::GetY() const noexcept
{
	return _values[1];
}

Vec2 Vec2::operator+(const Vec2& other) const noexcept
{
	return Vec2(_values[0] + other._values[0], _values[1] + other._values[1]);
}

Vec2 Vec2::operator-() const noexcept
{
	return Vec2(-_values[0], -_values[1]);
}

Vec2 Vec2::operator-(const Vec2& other) const noexcept
{
	return *this + (-other);
}


Vec2 operator*(float num, const Vec2& vector) noexcept
{
	return Vec2(vector._values[0] * num, vector._values[1] * num);
}

Vec2 operator*(const Vec2& vector, float num) noexcept
{
	return num * vector;
}

Vec2 Vec2::operator/(float num) const
{
	if (abs(num) == (float)1e-4)
		throw std::runtime_error("Math error: Attempt to divide vector2 by zero\n");
	return Vec2(_values[0] / num, _values[1] / num);
}


float Vec2::operator[](int index) const
{
	if (index < 0 || index >1)
		throw std::runtime_error("Attempt to get unexist vector component with operator[](parenthesis)");
	return _values[index];
}

float Vec2::SqrMagnitude() const noexcept
{
	return  _values[0] * _values[0] + _values[1] * _values[1];
}


float Vec2::Magnitude() const noexcept
{
	return std::sqrt(SqrMagnitude());
}


Vec2 Vec2::Normalized() const noexcept
{
	float value = _values[0] * _values[0] + _values[1] * _values[1]; // this is faster then value = Magnitude();
	value = std::sqrt(value);

	return Vec2(_values[0] / value, _values[1] / value);// faster then (*this/value)
}

void Vec2::Normalize() noexcept
{
	float len = Magnitude();
	for (int i = 0; i < 2; ++i)
	{
		_values[i] /= len;
	}

}

inline float Vec2::Dot(const Vec2& a, const Vec2& b) noexcept
{
	//its faster then using for. much faster
	return a._values[0] * b._values[0] + a._values[1] * b._values[1];
}


inline Vec2 Vec2::Normalized(const Vec2& a) noexcept
{
	return a.Normalized();
}

inline Vec2 Vec2::ClampMagnitude(const Vec2& vec, float maxLenght) noexcept
{
	float len = vec.Magnitude();
	bool isBig = len > maxLenght;
	return  (isBig*(maxLenght / len) + !isBig) * vec;
}

inline float Vec2::Distance(const Vec2& a, const Vec2& b) noexcept
{
	return (a - b).Magnitude();
}


inline Vec2 Vec2::LerpUnclamped(const Vec2& a, const Vec2& b, float t) noexcept
{
	return  (b - a)*t + a;
}

inline Vec2 Vec2::Lerp(const Vec2& a, const Vec2& b,float t) noexcept
{
	t = clamp(t,0.0f , 1.0f);

	return LerpUnclamped(a, b, t);
}

inline Vec2 Vec2::Scale(const Vec2& a, const Vec2& b) noexcept
{
	Vec2 v(a._values[0] * b._values[0], a._values[1] * b._values[1]);
	return v;
}


inline void Vec2::Scale(const Vec2& other) noexcept
{
	for (int i = 0; i < 2; ++i)
	{
		_values[i] *= other._values[i];
	}
}
