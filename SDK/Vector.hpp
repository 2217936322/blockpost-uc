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

    float length() const
    {
        return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    float length2D() const
    {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    std::string toString() const
    {
        return std::string{ "{ x: " + std::to_string(this->x) + ", y: " + std::to_string(this->y) + ", z: " + std::to_string(this->z) + " }" };
    }

    float x, y, z;
};

class Vector2 {
public:
    operator bool() const
    {
        return this->x || this->y;
    }

    float length() const
    {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    std::string toString() const
    {
        return std::string{ "{ x: " + std::to_string(this->x) + ", y: " + std::to_string(this->y) + " }" };
    }

	float x, y;
};

class Resolution {
public:
    operator bool() const
    {
        return this->width || this->height;
    }

    std::string toString() const
    {
        return std::string{ "{ width: " + std::to_string(this->width) + ", height: " + std::to_string(this->height) + " }" };
    }

    std::int32_t width, height;
};