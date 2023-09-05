#include "Quaternion.h"
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <iomanip>



template<class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
	return (v < lo) ? lo : (hi < v) ? hi : v;
}


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


inline Quaternion Quaternion::operator*(float num) const noexcept
{
	Quaternion res(_w * num, _axis * num);
	return res;
}

inline Quaternion Quaternion::operator+(const Quaternion& other) const noexcept
{
	Quaternion res(_w + other._w, _axis + other._axis);
	return res;
}

inline Quaternion Quaternion::operator-(const Quaternion& other) const noexcept
{
	Quaternion res(_w - other._w, _axis - other._axis);
	return res;
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
	/*
	float res = _w*_w;
	res += _axis.SqrMagnitude();
	res = sqrt(res);
	*/
	float res = Magnitude();
	_w /= res;
	_axis /= res;
}

inline float Quaternion::Dot(const Quaternion& a, const Quaternion& b) noexcept
{
	return a._w * b._w + Vec3::Dot(a._axis, b._axis);
}

inline std::string Quaternion::ToString() const noexcept
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << "( " << _w<< _axis.ToString() << " )";
	return ss.str();
}

Quaternion Quaternion ::Euler(float roll, float pitch, float yaw) noexcept
{
	float roll_half  = roll * 0.5f;
	float pitch_half = pitch * 0.5f;
	float yaw_half   = yaw * 0.5f;

	float cr = cos(roll_half);
	float sr = sin(roll_half);
	float cp = cos(pitch_half);
	float sp = sin(pitch_half);
	float cy = cos(yaw_half);
	float sy = sin(yaw_half);

	Quaternion q(
		cr * cp * cy + sr * sp * sy,
		sr * cp * cy - cr * sp * sy,
		cr * sp * cy + sr * cp * sy,
		cr * cp * sy - sr * sp * cy
	);

	return q;
}

inline Quaternion Quaternion::Euler(const Vec3& eulerAngles) noexcept
{
	return Quaternion::Euler(eulerAngles.GetX(), eulerAngles.GetY(), eulerAngles.GetZ());
}

inline float Quaternion::SqrMagnitude() const noexcept
{
	float res = _w * _w;
	res += _axis.SqrMagnitude();
	return res;
}

inline float Quaternion::Magnitude() const noexcept
{
	return sqrt(SqrMagnitude());
}

inline float Quaternion::Angle(const Quaternion& a, const Quaternion& b) noexcept
{
	return acos(Quaternion::Dot(a, b) / (a.Magnitude() * b.Magnitude()));
}

Quaternion Quaternion::SLerpUnclamped(const Quaternion& a, const Quaternion& b, float t) noexcept
{
	float omega = Quaternion::Angle(a, b);
	float omega_t = omega * t;
	Quaternion res = (a * sin(omega - omega_t) + b * sin(omega_t)) * (1 / sin(omega));

	return res;
}


Quaternion Quaternion::SLerp(const Quaternion& a, const Quaternion& b, float t) noexcept
{
	t = clamp(t, 0.0f, 1.0f);
	return SLerpUnclamped(a, b, t);
}

inline Quaternion Quaternion::LerpUnclamped(const Quaternion& a, const Quaternion& b, float t) noexcept
{
	return  (b - a) * t + a;
}

inline Quaternion Quaternion::Lerp(const Quaternion& a, const Quaternion& b, float t) noexcept
{
	t = clamp(t, 0.0f, 1.0f);
	return LerpUnclamped(a, b, t);
}


inline Quaternion Quaternion::FromToRotation(const Vec3& from, const Vec3& to) noexcept
{
	float w = sqrt(from.SqrMagnitude() * to.SqrMagnitude()) + Vec3::Dot(from, to);
	if (fabs(w) <= (float)1e-4) // vector colinear 
	{
		Vec3 any(-from.GetZ(), from.GetX(), from.GetY());// create any vectro non- colinear to From
		Quaternion res(0,Vec3::Cross(from, any));
		res.Normalize();
		return res;
	}

	Quaternion res(w, Vec3::Cross(from, to));
	res.Normalize();

	return res;


}

inline Quaternion Quaternion::AngleAxis(float angle, const Vec3& axis) noexcept
{
	float h = angle / 2;
	float cos_a = cos(h);
	float sin_a = sin(h);

	Quaternion res(cos_a, sin_a * Vec3::Normalized(axis));

	return res;
}


/// @see https://discussions.unity.com/t/what-is-the-source-code-of-quaternion-lookrotation/72474/2
inline Quaternion Quaternion::LookRotation(const Vec3& forward, const Vec3& up) noexcept
{
	///unimplemented
	return Quaternion::FromToRotation(forward, Vec3::Forward());
}
