#include "Quaternion.h"
#include <stdexcept>
#include <cmath>


Quaternion::Quaternion(float w,float x,float y,float z):_w(w),_axis(Vec3(x,y,z)){}

Quaternion::Quaternion(float w,const Vec3& vec):_w(w),_axis(vec){}


inline Vec3 Quaternion::GetAxises() const noexcept
{
	return _axis;
}

inline float Quaternion::GetW() const noexcept
{
	return _w;
}

inline float Quaternion::GetX() const noexcept
{
	return _axis.GetX();
}

inline float Quaternion::GetY() const noexcept
{
	return _axis.GetY();
}

inline float Quaternion::GetZ() const noexcept
{
	return _axis.GetZ();
}


float Quaternion::operator[](int index) const
{
	if (index < 0 || index > 3)
			throw std::runtime_error("Attempt to get unexist vector component with operator[](parenthesis)");
	return  index == 0 ?(_w):_axis[index - 1];
}



bool Quaternion::operator==(const Quaternion& other) const noexcept
{
	if (std::fabs(_w - other._w) > std::max(std::abs(_w), std::abs(other._w)) * (float)1e-4)
		return false;
	return _axis == other._axis;
}


Quaternion Quaternion::operator*(const Quaternion& other) const noexcept
{
	float a_x = _axis.GetX();
	float a_y = _axis.GetY();
	float a_z = _axis.GetZ();

	float b_w = other.GetW();
	float b_x = other.GetX();
	float b_y = other.GetY();
	float b_z = other.GetZ();

	float w = _w * b_w - a_x * b_x - a_y * b_y - a_z * b_z;
	float x = _w * b_x + a_x * b_w + a_y * b_z - a_z * b_y;
	float y = _w * b_y - a_x * b_z + a_y * b_w + a_z * b_x;
	float z = _w * b_z + a_x * b_y - a_y * b_x + a_z * b_w;

	Quaternion res(w, x, y, z);
	return res;
}

Vec3 Quaternion::operator*(const Vec3& other) const noexcept
{

	Quaternion res = (*this)*Quaternion(0.0f,other);
	res = res * Quaternion::Inverse(*this);
	return res.GetAxises();
}


inline Quaternion Quaternion::Identity() noexcept
{
	Quaternion res(1.0f, 0.0f, 0.0f, 0.0f);

	return res;
}

inline Quaternion Quaternion::Inverse(const Quaternion& a )noexcept
{
	Quaternion res(a._w,-a._axis);
	return res;
}

inline Quaternion Quaternion::Inverse() const noexcept
{
	Quaternion res(_w, -_axis);
	return res;
}


inline void Quaternion::Normalize() noexcept
{
	float res = _w*_w;
	res += _axis.SqrMagnitude();
	res = sqrt(res);

	_w /= res;
	_axis /= res;
}


