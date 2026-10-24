#pragma once

#include <cmath>
#include <algorithm>
#include <limits>

namespace G3D {

class Vector2 {
public:
    float x, y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x_, float y_) : x(x_), y(y_) {}
    explicit Vector2(float s) : x(s), y(s) {}

    static const Vector2& zero()  { static Vector2 v(0, 0); return v; }
    static const Vector2& one()   { static Vector2 v(1, 1); return v; }
    static const Vector2& unitX() { static Vector2 v(1, 0); return v; }
    static const Vector2& unitY() { static Vector2 v(0, 1); return v; }

    float& operator[](int i)             { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }

    Vector2 operator+(const Vector2& o) const { return Vector2(x + o.x, y + o.y); }
    Vector2 operator-(const Vector2& o) const { return Vector2(x - o.x, y - o.y); }
    Vector2 operator-() const                 { return Vector2(-x, -y); }

    Vector2 operator*(float s) const          { return Vector2(x * s, y * s); }
    Vector2 operator/(float s) const          { return Vector2(x / s, y / s); }
    Vector2 operator*(const Vector2& o) const { return Vector2(x * o.x, y * o.y); }
    Vector2 operator/(const Vector2& o) const { return Vector2(x / o.x, y / o.y); }

    Vector2& operator+=(const Vector2& o) { x += o.x; y += o.y; return *this; }
    Vector2& operator-=(const Vector2& o) { x -= o.x; y -= o.y; return *this; }
    Vector2& operator*=(float s)          { x *= s;   y *= s;   return *this; }
    Vector2& operator/=(float s)          { x /= s;   y /= s;   return *this; }

    bool operator==(const Vector2& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Vector2& o) const { return !(*this == o); }

    float squaredMagnitude() const { return x * x + y * y; }
    float magnitude() const        { return std::sqrt(squaredMagnitude()); }
    float length() const           { return magnitude(); }

    float unitize() {
        float len = magnitude();
        if (len > 0.0f) {
            float inv = 1.0f / len;
            x *= inv; y *= inv;
        }
        return len;
    }

    Vector2 unit() const {
        Vector2 v(*this);
        v.unitize();
        return v;
    }

    float dot(const Vector2& o) const { return x * o.x + y * o.y; }
    float cross(const Vector2& o) const { return x * o.y - y * o.x; }

    Vector2 min(const Vector2& o) const { return Vector2(std::min(x, o.x), std::min(y, o.y)); }
    Vector2 max(const Vector2& o) const { return Vector2(std::max(x, o.x), std::max(y, o.y)); }
    Vector2 abs() const { return Vector2(std::fabs(x), std::fabs(y)); }

    Vector2 clamp(const Vector2& lo, const Vector2& hi) const {
        return Vector2(std::max(lo.x, std::min(x, hi.x)),
                       std::max(lo.y, std::min(y, hi.y)));
    }

    Vector2 lerp(const Vector2& o, float t) const { return *this + (o - *this) * t; }

    bool isFinite() const { return std::isfinite(x) && std::isfinite(y); }

    bool fuzzyEq(const Vector2& o, float tol) const {
        return std::fabs(x - o.x) <= tol && std::fabs(y - o.y) <= tol;
    }

    float sum() const { return x + y; }
};

inline Vector2 operator*(float s, const Vector2& v) { return v * s; }

inline float dot(const Vector2& a, const Vector2& b) { return a.dot(b); }
inline float cross(const Vector2& a, const Vector2& b) { return a.cross(b); }

inline Vector2 abs(const Vector2& v) { return v.abs(); }
inline Vector2 min(const Vector2& a, const Vector2& b) { return a.min(b); }
inline Vector2 max(const Vector2& a, const Vector2& b) { return a.max(b); }
inline Vector2 lerp(const Vector2& a, const Vector2& b, float t) { return a.lerp(b, t); }

inline float distance(const Vector2& a, const Vector2& b) { return (a - b).magnitude(); }
inline float squaredDistance(const Vector2& a, const Vector2& b) { return (a - b).squaredMagnitude(); }

} // namespace G3D