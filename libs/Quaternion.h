#pragma once
#include "Vec3.h"
#include <string>

class Quaternion
{
public:

	Quaternion() = default;
	Quaternion(float, float, float, float);

	Quaternion(float, const Vec3&);


	
	Vec3 operator*(const Vec3&) const noexcept;
	Quaternion operator*(const Quaternion&) const noexcept;


	bool operator==(const Quaternion&) const noexcept;


	float operator[](int) const;

	/// @brief set to the given eulerAngles quaternion 
	void SetEulerAngles(const Vec3&) noexcept;

	/// @brief get euler angles of the quaternion
	Vec3& GetEqulerAngles() const noexcept;


	/// @brief get W conmonent of the Quaternion
	float GetW() const noexcept;

	/// @brief get X conmonent of the Quaternion
	float GetX() const noexcept;

	/// @brief get Y conmonent of the Quaternion
	float GetY() const noexcept;

	/// @brief get Z conmonent of the Quaternion
	float GetZ() const noexcept;

	Vec3 GetAxises() const noexcept;

	Quaternion Inverse() const noexcept;

	void Normalize() noexcept;

	float SqrMagnitude() const noexcept;

	float Magnitude() const noexcept;

	/// @brief set Quaternion as a rotation fromDirection to  toDirection 
	/// @param fromDirection - Initial direction  of the rotation.(non zero)
	/// @param toDirection - End direction of the rotation.(non zero)
	void SetFromToRotation(const Vec3& fromDirection, const Vec3& toDirection) noexcept;

	/// @brief Set Quaternion as a rotation with the specified forward and upwards directions.
	/// @param forward - The direction to look in.(non zero)
	/// @param up - The vector that defines in which direction up is.(non zero)
	/// @return identity Quaternion if forward if zero
	void SetLookRotation(const Vec3& forward, const Vec3& up = Vec3::Up()) noexcept;

	std::string ToString() const noexcept;

	/// @brief create a rotation fromDirection to  toDirection 
	/// @param fromDirection - Initial direction  of the rotation.(non zero)
	/// @param toDirection - End direction of the rotation.(non zero)
	static Quaternion FromToRotation(const Vec3& fromDirection, const Vec3& toDirection) noexcept;

	/// @brief Creates a rotation with the specified forward and upwards directions.
	/// @param forward - The direction to look in.(non zero)
	/// @param up - The vector that defines in which direction up is.(non zero)
	/// @return identity Quaternion if forward if zero
	static Quaternion LookRotation(const Vec3& forward, const Vec3& up = Vec3::Up()) noexcept;

	/// @brief return the angle in degrees benween two rotations
	static float Angle(const Quaternion& a, const Quaternion& b) noexcept;

	/// @brief create a rotation witch rotate angle degrees around axis
	/// @param angle - amount of degrees we want to rotate
	/// @param axis - axis of rotation 
	static Quaternion AngleAxis(float angle, const Vec3& axis) noexcept;

	/// @brief The dot product between two rotations
	static float Dot(const Quaternion&, const Quaternion&) noexcept;

	/// @brief Returns a rotation that rotates z degrees around the z axis, x degrees around the x axis, and y degrees around the y axis; applied in that order.
	static Quaternion Euler(float, float, float) noexcept;

	/// @brief Returns a rotation that rotates z degrees around the z axis, x degrees around the x axis, and y degrees around the y axis; applied in that order.
	static Quaternion Euler(const Vec3&) noexcept;

	/// @brief Returns the Inverse of the given rotation
	static Quaternion Inverse(const Quaternion&) noexcept;

	static Quaternion Identity() noexcept;

	/// @brief Interpolates between a and b by t and normalizes the result afterwards.The parameter t is clamped to the range[0, 1].
	static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t) noexcept;

	/// @brief Interpolates between a and b by t and normalizes the result afterwards.The parameter t is not clamped.
	/// @param a - quaternion with 
	static Quaternion LerpUnclamped(const Quaternion& a, const Quaternion& b, float t) noexcept;

	/// @brief Spherically interpolates between a and b by t and normalizes the result afterwards.The parameter t is clamped to the range[0, 1].
	static Quaternion SLerp(const Quaternion& a, const Quaternion& b, float t) noexcept;

	/// @brief Spherically interpolates between a and b by t and normalizes the result afterwards.The parameter t is not clamped.
	static Quaternion SLerpUnclamped(const Quaternion& a, const Quaternion& b, float t) noexcept;

	


private:

	Quaternion operator*(float) const noexcept;
	Quaternion operator+(const Quaternion&) const noexcept;
	Quaternion operator-(const Quaternion&) const noexcept;

	float _w;
	Vec3 _axis;
};

