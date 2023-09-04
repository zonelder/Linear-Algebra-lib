#pragma once
#include <string>

class  Vec3
{
public:
	Vec3(float x, float y,float z);
	Vec3(float x, float y);
	Vec3() = default;

	Vec3 operator+(const Vec3&) const noexcept;

	friend Vec3 operator*(float, const Vec3&) noexcept;
	friend Vec3 operator*(const Vec3&, float) noexcept;



	Vec3 operator/(float) const;
	void operator/=(float);

	Vec3 operator-() const noexcept;
	Vec3 operator-(const Vec3&) const noexcept;

	float operator[](int i) const;

	bool operator==(const Vec3&) const noexcept;

	/// @brief make this vector with a magnitude 1
	void Normalize() noexcept;

	/// @brief return copy of vector with magnitude 1
	Vec3 Normalized() const noexcept;

	/// @brief return Magnitude of the vector
	float Magnitude() const noexcept;

	/// @brief return sqr. Magnitude of the vector
	float SqrMagnitude() const noexcept;

	float GetX() const noexcept;
	float GetY() const noexcept;
	float GetZ() const noexcept;


	/// @brief Dot product of a two vectors 
	static float Dot(const Vec3&, const Vec3&) noexcept;
	static Vec3 Cross(const Vec3&, const Vec3&) noexcept;

	/// @brief return normed vector with same direction
	static Vec3 Normalized(const Vec3&) noexcept;

	/// @brief returns a copy of vector with its magnitude clamped to maxLength.
	static Vec3 ClampMagnitude(const Vec3& vector, float maxLen)  noexcept;

	/// @brief Returns the distance between vectors  a and b.
	static float Distance(const Vec3& a, const Vec3& b) noexcept;

	/// @brief Linearly interpolates between vectors a and b by t. t will be clamped in range  [0,1]
	static Vec3 Lerp(const Vec3& a, const Vec3& b, float t) noexcept;

	/// @brief Linearly interpolates between vectors a and b by t.
	static Vec3 LerpUnclamped(const Vec3& a, const Vec3& b, float t) noexcept;

	/// @brief Multiplies two vectors component-wise.
	static Vec3 Scale(const Vec3& vector, const Vec3& scale) noexcept;


	/// @brief Shorthand for writing Vec2(0, 1). 
	static Vec3 Up() noexcept;
	/// @brief Shorthand for writing Vec2(0, -1). 
	static Vec3 Down() noexcept;
	/// @brief Shorthand for writing Vec2(1, 0). 
	static Vec3 Right() noexcept;
	/// @brief Shorthand for writing Vec2(-1, 0). 
	static Vec3 Left() noexcept;
	/// @brief Shorthand for writing Vec2(1, 1). 
	static Vec3 One() noexcept;
	/// @brief Shorthand for writing Vec2(0, 0). 
	static Vec3 Zero() noexcept;

	static Vec3 Forward() noexcept;
	static Vec3 Back() noexcept;

	std::string ToString() const noexcept;

private:
	float _values[3];
};

