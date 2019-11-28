#pragma once

#include <cmath>

struct Coord3
{
    float x;
    float y;
    float z;

    Coord3(float x, float y, float z) : x(x), y(y), z(z) {}
    Coord3() : Coord3(0., 0., 0.) {}

    Coord3 operator+(const Coord3& other) const { return {x + other.x, y + other.y,z + other.z}; }
    Coord3 operator-(const Coord3& other) const { return {x - other.x, y - other.y,z - other.z}; }
    Coord3 operator*(float f) const { return {x * f, y * f, z * f}; }
    Coord3 operator/(float f) const { return {x / f, y / f, z / f}; }

    Coord3 Normalize() const
    {
        float length = std::sqrt(x * x + y * y + z * z);
        return *this / length;
    }

    static Coord3 CrossProduct(const Coord3& a, const Coord3& b)
    {
        float x = (a.y * b.z) - (a.z * b.y);
        float y = (a.z * b.x) - (a.x * b.z);
        float z = (a.x * b.y) - (a.y * b.x);

        return {x, y, z};
    }
};