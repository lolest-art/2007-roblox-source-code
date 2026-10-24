#pragma once

#include "g3dmath.h"
#include "Vector2.h"
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <limits>

namespace G3D {

class Vector3 {
public:
    float x, y, z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    explicit Vector3(float s) : x(s), y(s), z(s) {}

    static const Vector3& zero()    { static Vector3 v(0, 0, 0); return v; }
    static const Vector3& one()     { static Vector3 v(1, 1, 1); return v; }
    static const Vector3& unitX()   { static Vector3 v(1, 0, 0); return v; }
    static const Vector3& unitY()   { static Vector3 v(0, 1, 0); return v; }
    static const Vector3& unitZ()   { static Vector3 v(0, 0, 1); return v; }
    static const Vector3& inf()     { static Vector3 v( std::numeric_limits<float>::infinity(),
                                                        std::numeric_limits<float>::infinity(),
                                                        std::numeric_limits<float>::infinity());
                                      return v; }
    static const Vector3& nan()     { static Vector3 v( std::numeric_limits<float>::quiet_NaN(),
                                                        std::numeric_limits<float>::quiet_NaN(),
                                                        std::numeric_limits<float>::quiet_NaN());
                                      return v; }

    // ── Indexing ────────────────────────────────────────────────────────
    float& operator[](int i)             { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }

    // ── Implicit conversion to contiguous float array ───────────────────
    // Math::legalCameraCoord does:
    //   const float* transMatArr = (const float*)c.translation;
    operator float*()             { return &x; }
    operator const float*() const { return &x; }

    // ── Arithmetic ──────────────────────────────────────────────────────
    Vector3 operator+(const Vector3& o) const { return Vector3(x + o.x, y + o.y, z + o.z); }
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
    Vector3 operator-() const                 { return Vector3(-x, -y, -z); }

    Vector3 operator*(float s) const          { return Vector3(x * s, y * s, z * s); }
    Vector3 operator/(float s) const          { return Vector3(x / s, y / s, z / s); }

    // Component-wise multiply and divide.
Vector3 operator*(const Vector3& o) const { return Vector3(x * o.x, y * o.y, z * o.z); }
    //Vector3 operator*(const Vector3& o) const { return Vector3(x * o.x, y * o.y, z * o.z); }
    Vector3 componentwiseMul(const Vector3& o) const { return Vector3(x * o.x, y * o.y, z * o.z); } 
    Vector3 operator/(const Vector3& o) const { return Vector3(x / o.x, y / o.y, z / o.z); }

    Vector3& operator+=(const Vector3& o) { x += o.x; y += o.y; z += o.z; return *this; }
    Vector3& operator-=(const Vector3& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
    Vector3& operator*=(float s)          { x *= s;   y *= s;   z *= s;   return *this; }
    Vector3& operator/=(float s)          { x /= s;   y /= s;   z /= s;   return *this; }
    Vector3& operator*=(const Vector3& o) { x *= o.x; y *= o.y; z *= o.z; return *this; }
    Vector3& operator/=(const Vector3& o) { x /= o.x; y /= o.y; z /= o.z; return *this; }

    // ── Comparison ──────────────────────────────────────────────────────
    bool operator==(const Vector3& o) const { return x == o.x && y == o.y && z == o.z; }
    bool operator!=(const Vector3& o) const { return !(*this == o); }
    bool operator<(const Vector3& o) const {
        if (x < o.x) return true;
        if (x > o.x) return false;
        if (y < o.y) return true;
        if (y > o.y) return false;
        return z < o.z;
    }

    // ── Length / normalization ──────────────────────────────────────────
    float squaredMagnitude() const { return x * x + y * y + z * z; }
    float magnitude() const        { return std::sqrt(squaredMagnitude()); }
    float length() const           { return magnitude(); }

    float unitize() {
        float len = magnitude();
        if (len > 0.0f) {
            float inv = 1.0f / len;
            x *= inv; y *= inv; z *= inv;
        }
        return len;
    }

    Vector3 unit() const { Vector3 v(*this); v.unitize(); return v; }
    Vector3 direction() const { return unit(); }

    // ── Dot / cross ─────────────────────────────────────────────────────
    float dot(const Vector3& o) const {
        return x * o.x + y * o.y + z * o.z;
    }

    Vector3 cross(const Vector3& o) const {
        return Vector3(
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        );
    }

    // ── Component-wise helpers ──────────────────────────────────────────
    Vector3 min(const Vector3& o) const {
        return Vector3(std::min(x, o.x), std::min(y, o.y), std::min(z, o.z));
    }

    Vector3 max(const Vector3& o) const {
        return Vector3(std::max(x, o.x), std::max(y, o.y), std::max(z, o.z));
    }

    Vector3 abs() const {
        return Vector3(std::fabs(x), std::fabs(y), std::fabs(z));
    }

    Vector3 clamp(const Vector3& lo, const Vector3& hi) const {
        return Vector3(
            std::max(lo.x, std::min(x, hi.x)),
            std::max(lo.y, std::min(y, hi.y)),
            std::max(lo.z, std::min(z, hi.z))
        );
    }

    Vector3 lerp(const Vector3& o, float t) const {
        return *this + (o - *this) * t;
    }

    // ── Queries ─────────────────────────────────────────────────────────
    bool isFinite() const {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }

    bool isZero() const { return x == 0.0f && y == 0.0f && z == 0.0f; }

    bool isUnit(float tol = 1e-4f) const {
        return std::fabs(squaredMagnitude() - 1.0f) <= tol;
    }

    bool fuzzyEq(const Vector3& o, float tol) const {
        return std::fabs(x - o.x) <= tol
            && std::fabs(y - o.y) <= tol
            && std::fabs(z - o.z) <= tol;
    }

    int primaryAxis() const {
        float ax = std::fabs(x), ay = std::fabs(y), az = std::fabs(z);
        if (ax >= ay && ax >= az) return 0;
        if (ay >= az) return 1;
        return 2;
    }

    float sum() const { return x + y + z; }
};

// ── Free functions ──────────────────────────────────────────────────────
inline Vector3 operator*(float s, const Vector3& v) { return v * s; }

inline float dot(const Vector3& a, const Vector3& b) { return a.dot(b); }
inline Vector3 cross(const Vector3& a, const Vector3& b) { return a.cross(b); }

inline Vector3 abs(const Vector3& v) { return v.abs(); }
inline Vector3 min(const Vector3& a, const Vector3& b) { return a.min(b); }
inline Vector3 max(const Vector3& a, const Vector3& b) { return a.max(b); }
inline Vector3 lerp(const Vector3& a, const Vector3& b, float t) { return a.lerp(b, t); }

inline float distance(const Vector3& a, const Vector3& b) { return (a - b).magnitude(); }
inline float squaredDistance(const Vector3& a, const Vector3& b) { return (a - b).squaredMagnitude(); }

} // namespace G3D