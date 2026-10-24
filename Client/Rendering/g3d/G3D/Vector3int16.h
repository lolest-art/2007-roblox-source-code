#pragma once

#include "Vector3.h"
#include <cstdint>
#include <algorithm>

namespace G3D {

class Vector3int16 {
public:
    int16_t x, y, z;

    Vector3int16() : x(0), y(0), z(0) {}
    Vector3int16(int16_t x_, int16_t y_, int16_t z_) : x(x_), y(y_), z(z_) {}

    // Vector3 -> Vector3int16 uses TRUNCATION (not rounding).
    explicit Vector3int16(const Vector3& v)
        : x(static_cast<int16_t>(v.x))
        , y(static_cast<int16_t>(v.y))
        , z(static_cast<int16_t>(v.z)) {}

    int16_t& operator[](int i)             { return (&x)[i]; }
    const int16_t& operator[](int i) const { return (&x)[i]; }

    Vector3int16 operator+(const Vector3int16& o) const { return {int16_t(x+o.x), int16_t(y+o.y), int16_t(z+o.z)}; }
    Vector3int16 operator-(const Vector3int16& o) const { return {int16_t(x-o.x), int16_t(y-o.y), int16_t(z-o.z)}; }
    Vector3int16 operator-() const                      { return {int16_t(-x), int16_t(-y), int16_t(-z)}; }

    Vector3int16 operator*(int s) const { return {int16_t(x*s), int16_t(y*s), int16_t(z*s)}; }

    bool operator==(const Vector3int16& o) const { return x==o.x && y==o.y && z==o.z; }
    bool operator!=(const Vector3int16& o) const { return !(*this == o); }

    bool operator<(const Vector3int16& o) const {
        if (x < o.x) return true;
        if (x > o.x) return false;
        if (y < o.y) return true;
        if (y > o.y) return false;
        return z < o.z;
    }

    Vector3 toVector3() const { return Vector3(float(x), float(y), float(z)); }
};

inline Vector3int16 min(const Vector3int16& a, const Vector3int16& b) {
    return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
}
inline Vector3int16 max(const Vector3int16& a, const Vector3int16& b) {
    return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
}

} // namespace G3D