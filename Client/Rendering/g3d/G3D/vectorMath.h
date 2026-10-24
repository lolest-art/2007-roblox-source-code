#pragma once

#include "Vector3.h"
#include "Matrix3.h"
#include "CoordinateFrame.h"
#include <cmath>

namespace G3D {

// Return the axis of rotation from a rotation matrix. Used by some
// transform code paths.
inline Vector3 rotationAxis(const Matrix3& R) {
    float trace = R[0][0] + R[1][1] + R[2][2];
    float angle = std::acos((trace - 1.0f) * 0.5f);
    if (std::fabs(angle) < 1e-6f) return Vector3(1, 0, 0);

    float s = 2.0f * std::sin(angle);
    if (std::fabs(s) < 1e-6f) return Vector3(1, 0, 0);

    return Vector3(
        (R[2][1] - R[1][2]) / s,
        (R[0][2] - R[2][0]) / s,
        (R[1][0] - R[0][1]) / s
    );
}

// Build a rotation matrix that rotates unit vector `from` onto unit
// vector `to` (Rodrigues' formula via the minimal rotation).
inline Matrix3 rotationMatrixFromTo(const Vector3& from, const Vector3& to) {
    Vector3 v = from.cross(to);
    float c = from.dot(to);

    if (v.squaredMagnitude() < 1e-12f) {
        if (c > 0.0f) return Matrix3::identity();
        // 180° rotation — pick an arbitrary perpendicular axis
        Vector3 axis = std::fabs(from.x) < 0.9f
            ? Vector3(1, 0, 0).cross(from).unit()
            : Vector3(0, 1, 0).cross(from).unit();
        return Matrix3(
            2*axis.x*axis.x - 1, 2*axis.x*axis.y,     2*axis.x*axis.z,
            2*axis.x*axis.y,     2*axis.y*axis.y - 1, 2*axis.y*axis.z,
            2*axis.x*axis.z,     2*axis.y*axis.z,     2*axis.z*axis.z - 1
        );
    }

    // Skew-symmetric cross matrix
    Matrix3 K(
         0,   -v.z,  v.y,
         v.z,  0,   -v.x,
        -v.y,  v.x,  0
    );

    float s = v.magnitude();
    float invS2 = 1.0f / (s * s);

    return Matrix3::identity() + K * invS2 * s + K * K * ((1.0f - c) * invS2);
}

// Convert a rotation matrix to axis-angle.
inline void toAxisAngle(const Matrix3& R, Vector3& axis, float& angle) {
    float trace = R[0][0] + R[1][1] + R[2][2];
    angle = std::acos(std::max(-1.0f, std::min(1.0f, (trace - 1.0f) * 0.5f)));

    if (std::fabs(angle) < 1e-6f) {
        axis = Vector3(1, 0, 0);
        angle = 0.0f;
        return;
    }

    float s = 2.0f * std::sin(angle);
    if (std::fabs(s) < 1e-6f) {
        // Near 180 degrees — use diagonal method
        float xx = (R[0][0] + 1.0f) * 0.5f;
        float yy = (R[1][1] + 1.0f) * 0.5f;
        float zz = (R[2][2] + 1.0f) * 0.5f;
        float xy = (R[0][1] + R[1][0]) * 0.25f;
        float xz = (R[0][2] + R[2][0]) * 0.25f;
        float yz = (R[1][2] + R[2][1]) * 0.25f;

        if (xx > yy && xx > zz) {
            axis.x = std::sqrt(std::max(0.0f, xx));
            axis.y = xy / axis.x;
            axis.z = xz / axis.x;
        } else if (yy > zz) {
            axis.y = std::sqrt(std::max(0.0f, yy));
            axis.x = xy / axis.y;
            axis.z = yz / axis.y;
        } else {
            axis.z = std::sqrt(std::max(0.0f, zz));
            axis.x = xz / axis.z;
            axis.y = yz / axis.z;
        }
        return;
    }

    axis = Vector3(
        (R[2][1] - R[1][2]) / s,
        (R[0][2] - R[2][0]) / s,
        (R[1][0] - R[0][1]) / s
    );
}

} // namespace G3D