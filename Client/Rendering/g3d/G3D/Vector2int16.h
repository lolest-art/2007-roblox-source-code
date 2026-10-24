#pragma once

#include "Vector2.h"
#include <cstdint>

namespace G3D {

class Vector2int16 {
public:
    int16_t x, y;

    Vector2int16() : x(0), y(0) {}
    Vector2int16(int16_t x_, int16_t y_) : x(x_), y(y_) {}

    explicit Vector2int16(const Vector2& v)
        : x(static_cast<int16_t>(v.x))
        , y(static_cast<int16_t>(v.y)) {}

    int16_t& operator[](int i)             { return (&x)[i]; }
    const int16_t& operator[](int i) const { return (&x)[i]; }

    Vector2int16 operator+(const Vector2int16& o) const { return {int16_t(x+o.x), int16_t(y+o.y)}; }
    Vector2int16 operator-(const Vector2int16& o) const { return {int16_t(x-o.x), int16_t(y-o.y)}; }

    bool operator==(const Vector2int16& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Vector2int16& o) const { return !(*this == o); }

    Vector2 toVector2() const { return Vector2(float(x), float(y)); }
};

} // namespace G3D