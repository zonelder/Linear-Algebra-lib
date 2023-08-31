#pragma once
#include <string>

class  Vec2
{
public:
	Vec2(float x, float y);
	Vec2() = default;
	
	Vec2 operator+(const Vec2&) const noexcept;

	friend Vec2 operator*(float, const Vec2&) noexcept;
	friend Vec2 operator*(const Vec2&,float) noexcept;

	Vec2 operator/(float) const;

	Vec2 operator-() const noexcept;
	Vec2 operator-(const Vec2&) const noexcept;

	float operator[](int i) const;

	bool operator==(const Vec2&) const noexcept;

	/// @brief make this vector with a magnitude 1
	void Normalize() noexcept;

	/// @brief return copy of vector with magnitude 1
	Vec2 Normalized() const noexcept;

	/// @brief return Magnitude of the vector
	float Magnitude() const noexcept;

	/// @brief return sqr. Magnitude of the vector
	float SqrMagnitude() const noexcept;

	float getX() const noexcept;
	float getY() const noexcept;


	/// @brief Dot product of a two vectors 
	static float Dot(const Vec2&, const Vec2&) noexcept;

	/// @brief return normed vector with same direction
	static Vec2 Normalized(const Vec2&) noexcept;

	/// @brief returns a copy of vector with its magnitude clamped to maxLength.
	static Vec2 ClampMagnitude(const Vec2& vector,float maxLen)  noexcept;

	/// @brief Returns the distance between vectors  a and b.
	static float Distance(const Vec2& a, const Vec2& b) noexcept;

	/// @brief Linearly interpolates between vectors a and b by t. t will be clamped in range  [0,1]
	static Vec2 Lerp(const Vec2& a, const Vec2& b, float t) noexcept;

	/// @brief Linearly interpolates between vectors a and b by t.
	static Vec2 LerpUnclamped(const Vec2& a, const Vec2& b, float t) noexcept;

	/// @brief Multiplies two vectors component-wise.
	static Vec2 Scale(const Vec2& vector, const Vec2& scale) noexcept;


	/// @brief Shorthand for writing Vec2(0, 1). 
	static Vec2 Up() noexcept;
	/// @brief Shorthand for writing Vec2(0, -1). 
	static Vec2 Down() noexcept;
	/// @brief Shorthand for writing Vec2(1, 0). 
	static Vec2 Right() noexcept;
	/// @brief Shorthand for writing Vec2(-1, 0). 
	static Vec2 Left() noexcept;
	/// @brief Shorthand for writing Vec2(1, 1). 
	static Vec2 One() noexcept;
	/// @brief Shorthand for writing Vec2(0, 0). 
	static Vec2 Zero() noexcept;

	std::string ToString() const noexcept;

private:
	float _values[2];
};

