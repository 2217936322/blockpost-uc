#pragma once

constexpr auto RAD2DEG = [](float radians) { return radians * 180.0f / static_cast<float>(M_PI); };

class Vector3 {
public:
	operator bool() const
	{
		return this->x || this->y || this->z;
	}

	Vector3& operator+=(const Vector3& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}

	Vector3 operator-(const Vector3& v) const
	{
		return Vector3{ this->x - v.x, this->y - v.y, this->z - v.z };
	}

	Vector3 operator+(const Vector3& v) const
	{
		return Vector3{ this->x + v.x, this->y + v.y, this->z + v.z };
	}

	Vector3 operator*(const Vector3& v) const
	{
		return Vector3{ this->x * v.x, this->y * v.y, this->z * v.z };
	}

	Vector3 operator*(float mul) const
	{
		return Vector3{ this->x * mul, this->y * mul, this->z * mul };
	}

	float x, y, z;
};

class Vector2 {
public:
	operator bool() const
	{
		return this->x || this->y;
	}

	Vector2& operator-=(const Vector2& v)
	{
		this->x += v.x;
		this->y += v.y;
		return *this;
	}

	Vector2 operator*(float mul) const
	{
		return Vector2{ this->x * mul, this->y * mul };
	}

	float length() const
	{
		return std::sqrt(this->x * this->x + this->y * this->y);
	}

	float x, y;
};

class Resolution {
public:
	operator bool() const
	{
		return this->width || this->height;
	}

	std::int32_t width, height;
};