#pragma once

#include "Vector3.h"
#include "Matrix3.h"
#include <cmath>

namespace G3D {

class Quaternion {
public:
    float w, x, y, z;

    Quaternion() : w(1), x(0), y(0), z(0) {}
    Quaternion(float w_, float x_, float y_, float z_)
        : w(w_), x(x_), y(y_), z(z_) {}

    // From a 3x3 rotation matrix (Shepperd's method).
    explicit Quaternion(const Matrix3& m) {
        float trace = m[0][0] + m[1][1] + m[2][2];
        if (trace > 0.0f) {
            float s = 0.5f / std::sqrt(trace + 1.0f);
            w = 0.25f / s;
            x = (m[2][1] - m[1][2]) * s;
            y = (m[0][2] - m[2][0]) * s;
            z = (m[1][0] - m[0][1]) * s;
        } else if (m[0][0] > m[1][1] && m[0][0] > m[2][2]) {
            float s = 2.0f * std::sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]);
            w = (m[2][1] - m[1][2]) / s;
            x = 0.25f * s;
            y = (m[0][1] + m[1][0]) / s;
            z = (m[0][2] + m[2][0]) / s;
        } else if (m[1][1] > m[2][2]) {
            float s = 2.0f * std::sqrt(1.0f + m[1][1] - m[0][0] - m[2][2]);
            w = (m[0][2] - m[2][0]) / s;
            x = (m[0][1] + m[1][0]) / s;
            y = 0.25f * s;
            z = (m[1][2] + m[2][1]) / s;
        } else {
            float s = 2.0f * std::sqrt(1.0f + m[2][2] - m[0][0] - m[1][1]);
            w = (m[1][0] - m[0][1]) / s;
            x = (m[0][2] + m[2][0]) / s;
            y = (m[1][2] + m[2][1]) / s;
            z = 0.25f * s;
        }
    }

    // Axis-angle constructor.
    // NOTE: This is the FIXED version. Real G3D treats `axis` as a rotation
    // axis, normalizes it, and produces a proper unit quaternion.
    // At angle == 0 this returns identity (1,0,0,0), NOT a pure quaternion.
    // SimBody.cpp's Quaternion(velocity.rotational, 0) relies on this:
    // when angular velocity is zero, the incremental rotation is identity.
    Quaternion(const Vector3& axis, float angle) {
        float len = axis.magnitude();
        if (len < 1e-12f) {
            // Degenerate axis: return identity regardless of angle.
            w = 1.0f; x = y = z = 0.0f;
            return;
        }
        float half = angle * 0.5f;
        float s = std::sin(half);
        float invLen = 1.0f / len;
        w = std::cos(half);
        x = axis.x * invLen * s;
        y = axis.y * invLen * s;
        z = axis.z * invLen * s;
    }

    static const Quaternion& identity() {
        static Quaternion q(1, 0, 0, 0);
        return q;
    }

    Quaternion operator*(const Quaternion& o) const {
        return Quaternion(
            w*o.w - x*o.x - y*o.y - z*o.z,
            w*o.x + x*o.w + y*o.z - z*o.y,
            w*o.y - x*o.z + y*o.w + z*o.x,
            w*o.z + x*o.y - y*o.x + z*o.w
        );
    }

    Quaternion operator*(float s) const { return Quaternion(w*s, x*s, y*s, z*s); }
    Quaternion operator+(const Quaternion& o) const { return Quaternion(w+o.w, x+o.x, y+o.y, z+o.z); }
    Quaternion operator-(const Quaternion& o) const { return Quaternion(w-o.w, x-o.x, y-o.y, z-o.z); }
    Quaternion operator-() const { return Quaternion(-w, -x, -y, -z); }

    Quaternion& operator*=(float s) { w*=s; x*=s; y*=s; z*=s; return *this; }
    Quaternion& operator*=(const Quaternion& o) { *this = *this * o; return *this; }
    Quaternion& operator+=(const Quaternion& o) { w+=o.w; x+=o.x; y+=o.y; z+=o.z; return *this; }

    bool operator==(const Quaternion& o) const { return w==o.w && x==o.x && y==o.y && z==o.z; }
    bool operator!=(const Quaternion& o) const { return !(*this == o); }

    float squaredMagnitude() const { return w*w + x*x + y*y + z*z; }
    float magnitude() const { return std::sqrt(squaredMagnitude()); }

    void normalize() {
        float m = magnitude();
        if (m > 0.0f) { float inv = 1.0f/m; w*=inv; x*=inv; y*=inv; z*=inv; }
    }
    Quaternion unit() const { Quaternion q(*this); q.normalize(); return q; }
    Quaternion conjugate() const { return Quaternion(w, -x, -y, -z); }
    Quaternion inverse() const {
        float m2 = squaredMagnitude();
        if (m2 <= 0.0f) return Quaternion();
        float inv = 1.0f/m2;
        return Quaternion(w*inv, -x*inv, -y*inv, -z*inv);
    }

    void toRotationMatrix(Matrix3& m) const {
        float xx = x*x, yy = y*y, zz = z*z;
        float xy = x*y, xz = x*z, yz = y*z;
        float wx = w*x, wy = w*y, wz = w*z;
        m[0][0] = 1.0f - 2.0f*(yy + zz);
        m[0][1] = 2.0f*(xy - wz);
        m[0][2] = 2.0f*(xz + wy);
        m[1][0] = 2.0f*(xy + wz);
        m[1][1] = 1.0f - 2.0f*(xx + zz);
        m[1][2] = 2.0f*(yz - wx);
        m[2][0] = 2.0f*(xz - wy);
        m[2][1] = 2.0f*(yz + wx);
        m[2][2] = 1.0f - 2.0f*(xx + yy);
    }

    Matrix3 toRotationMatrix() const { Matrix3 m; toRotationMatrix(m); return m; }

    Vector3 rotate(const Vector3& v) const {
        Vector3 u(x, y, z);
        float s = w;
        return 2.0f*u.dot(v)*u + (s*s - u.dot(u))*v + 2.0f*s*u.cross(v);
    }

    static Quaternion fromVectorToVector(const Vector3& a, const Vector3& b) {
        Vector3 ua = a.unit();
        Vector3 ub = b.unit();
        float d = ua.dot(ub);
        if (d > 1.0f - 1e-6f) return identity();
        if (d < -1.0f + 1e-6f) {
            Vector3 axis = std::fabs(ua.x) < 0.9f
                ? Vector3(1,0,0).cross(ua).unit()
                : Vector3(0,1,0).cross(ua).unit();
            return Quaternion(axis, 3.14159265f);
        }
        Vector3 axis = ua.cross(ub);
        float s = std::sqrt((1.0f + d) * 2.0f);
        float invS = 1.0f / s;
        return Quaternion(s*0.5f, axis.x*invS, axis.y*invS, axis.z*invS);
    }
};

inline Quaternion operator*(float s, const Quaternion& q) { return q * s; }

} // namespace G3D