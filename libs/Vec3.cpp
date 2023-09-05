#include "Vec3.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>



template<class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
	return (v < lo) ? lo : (hi < v) ? hi : v;
}

Vec3::Vec3(float x, float y,float z)
{
	_values[0] = x;
	_values[1] = y;
	_values[2] = z;
}

Vec3::Vec3(float x, float y) :Vec3(x, y, 0.0f){}

std::string Vec3::ToString() const noexcept
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << "( " << _values[0] << " , " << _values[1] << " , " << _values[2] << " )";
	return ss.str();
}

Vec3 Vec3::Up() noexcept
{
	Vec3 a(0, 1, 0);
	return	a;
}

Vec3 Vec3::Down() noexcept
{
	Vec3 a(0, -1, 0);
	return	a;
}

Vec3 Vec3::Right() noexcept
{
	Vec3 a(1, 0, 0);
	return	a;
}

Vec3 Vec3::Left() noexcept
{
	Vec3 a(-1, 0, 0);
	return	a;
}

Vec3 Vec3::One() noexcept
{
	Vec3 a(1, 1, 0);
	return	a;
}

Vec3 Vec3::Zero() noexcept
{
	Vec3 a(0, 0, 0);
	return	a;
}

bool  Vec3::operator==(const Vec3& other) const noexcept
{
	for (int i = 0; i < 3; ++i)
	{
		if (std::fabs(_values[i] - other._values[i]) > std::max(std::abs(_values[i]), std::abs(other._values[i])) * (float)1e-4)
		{
			return false;
		}
	}
	return true;
}


float Vec3::GetX() const noexcept
{
	return _values[0];
}

float Vec3::GetY() const noexcept
{
	return _values[1];
}

float Vec3::GetZ() const noexcept
{
	return _values[2];
}

Vec3 Vec3::operator+(const Vec3& other) const noexcept
{
	return Vec3(_values[0] + other._values[0], _values[1] + other._values[1], _values[2] + other._values[2]);
}

Vec3 Vec3::operator-() const noexcept
{
	return Vec3(-_values[0], -_values[1], -_values[2]);
}

Vec3 Vec3::operator-(const Vec3& other) const noexcept
{
	return *this + (-other);
}


Vec3 operator*(float num, const Vec3& vector) noexcept
{
	return Vec3(vector._values[0] * num, vector._values[1] * num,vector._values[2]*num);
}

Vec3 operator*(const Vec3& vector, float num) noexcept
{
	return num * vector;
}

Vec3 Vec3::operator/(float num) const
{
	if (abs(num) == (float)1e-4)
		throw std::runtime_error("Math error: Attempt to divide vector2 by zero\n");
	return Vec3(_values[0] / num, _values[1] / num, _values[2]/num);
}

void Vec3::operator/=(float num)
{
	*this =  (*this) / num;
}


float Vec3::operator[](int index) const
{
	if (index < 0 || index >1)
		throw std::runtime_error("Attempt to get unexist vector component with operator[](parenthesis)");
	return _values[index];
}


float Vec3::SqrMagnitude() const noexcept
{
	return  _values[0] * _values[0] + _values[1] * _values[1] + _values[2]*_values[2] ;
}


float Vec3::Magnitude() const noexcept
{
	return std::sqrt(SqrMagnitude());
}


Vec3 Vec3::Normalized() const noexcept
{
	float value = _values[0] * _values[0] + _values[1] * _values[1]; // this is faster then value = Magnitude();
	value = std::sqrt(value);

	return Vec3(_values[0] / value, _values[1] / value, _values[2]/value);// faster then (*this/value)
}

void Vec3::Normalize() noexcept
{
	float len = Magnitude();
	for (int i = 0; i < 2; ++i)
	{
		_values[i] /= len;
	}

}

float Vec3::Dot(const Vec3& a, const Vec3& b) noexcept
{
	//its faster then using for. much faster
	return a._values[0] * b._values[0] + a._values[1] * b._values[1] + a._values[2] * b._values[2];
}


inline Vec3 Vec3::Normalized(const Vec3& a) noexcept
{
	return a.Normalized();
}

inline Vec3 Vec3::ClampMagnitude(const Vec3& vec, float maxLenght) noexcept
{
	float len = vec.Magnitude();
	bool isBig = len > maxLenght;
	return  (isBig * (maxLenght / len) + !isBig) * vec;
}

inline float Vec3::Distance(const Vec3& a, const Vec3& b) noexcept
{
	return (a - b).Magnitude();
}


inline Vec3 Vec3::LerpUnclamped(const Vec3& a, const Vec3& b, float t) noexcept
{
	return  (b - a) * t + a;
}

inline Vec3 Vec3::Lerp(const Vec3& a, const Vec3& b, float t) noexcept
{
	t = clamp(t, 0.0f, 1.0f);
	return LerpUnclamped(a, b, t);
}

inline Vec3 Vec3::Scale(const Vec3& a, const Vec3& b) noexcept
{
	Vec3 v(a._values[0] * b._values[0], a._values[1] * b._values[1], a._values[2] * b._values[2]);
	return v;
}

inline Vec3 Vec3::Cross(const Vec3& a, const Vec3& b) noexcept
{
	float ax = a.GetX();
	float ay = a.GetY();
	float az = a.GetZ();

	float bx = b.GetX();
	float by = b.GetY();
	float bz = b.GetZ();
	Vec3 res(
		ay * bz - by * az,
		ax * bz - bx * az,
		ax * by - bx * ay
	);

	return res;
}
