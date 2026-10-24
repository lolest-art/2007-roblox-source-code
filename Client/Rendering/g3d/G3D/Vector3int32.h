#pragma once

#include "Vector3.h"
#include <cstdint>
#include <cmath>
#include <algorithm>

namespace G3D {

class Vector3int32 {
public:
    int32_t x, y, z;

    Vector3int32() : x(0), y(0), z(0) {}
    Vector3int32(int32_t x_, int32_t y_, int32_t z_) : x(x_), y(y_), z(z_) {}

    explicit Vector3int32(const Vector3& v)
        : x(static_cast<int32_t>(v.x))
        , y(static_cast<int32_t>(v.y))
        , z(static_cast<int32_t>(v.z)) {}

    static Vector3int32 floor(const Vector3& v) {
        return { int32_t(std::floor(v.x)),
                 int32_t(std::floor(v.y)),
                 int32_t(std::floor(v.z)) };
    }

    int32_t& operator[](int i)             { return (&x)[i]; }
    const int32_t& operator[](int i) const { return (&x)[i]; }

    Vector3int32 operator+(const Vector3int32& o) const { return {x+o.x, y+o.y, z+o.z}; }
    Vector3int32 operator-(const Vector3int32& o) const { return {x-o.x, y-o.y, z-o.z}; }

    bool operator==(const Vector3int32& o) const { return x==o.x && y==o.y && z==o.z; }
    bool operator!=(const Vector3int32& o) const { return !(*this == o); }

    bool operator<(const Vector3int32& o) const {
        if (x < o.x) return true;
        if (x > o.x) return false;
        if (y < o.y) return true;
        if (y > o.y) return false;
        return z < o.z;
    }

    Vector3 toVector3() const { return Vector3(float(x), float(y), float(z)); }
};

} // namespace G3D