#include "Vec2.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <stdexcept>

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

Vec2 Vec2::Up() noexcept
{
	Vec2 a(0, 1);
	return	a;
}

Vec2 Vec2::Down() noexcept
{
	Vec2 a(0, -1);
	return	a;
}

Vec2 Vec2::Right() noexcept
{
	Vec2 a(1, 0);
	return	a;
}

Vec2 Vec2::Left() noexcept
{
	Vec2 a(-1, 0);
	return	a;
}

Vec2 Vec2::One() noexcept
{
	Vec2 a(1, 1);
	return	a;
}

Vec2 Vec2::Zero() noexcept
{
	Vec2 a(0, 0);
	return	a;
}

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


float Vec2::getX() const noexcept
{
	return _values[0];
}

float Vec2::getY() const noexcept
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


float Vec2::operator[](int index) const noexcept
{
	if (index < 0 || index >1)
		throw std::runtime_error("Attempt to get unexist vector component with operator[](parenthesis)");
	return _values[index];
}
