#pragma once

#include "Vector3.h"
#include <cmath>
#include <cstring>

namespace G3D {

class Matrix3 {
public:
    float m[3][3];

    Matrix3() {
        std::memset(m, 0, sizeof(m));
    }

    Matrix3(float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22)
    {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
    }

    static const Matrix3& zero() {
        static Matrix3 v;
        return v;
    }

    static const Matrix3& identity() {
        static Matrix3 v(1, 0, 0,
                         0, 1, 0,
                         0, 0, 1);
        return v;
    }

    // ── Row access ──────────────────────────────────────────────────────
    float* operator[](int row)             { return m[row]; }
    const float* operator[](int row) const { return m[row]; }

    // ── Implicit conversion to contiguous 9-float array (row-major) ────
    // Math::legalCameraCoord does:
    //   const float* rotMatArr = (const float*)c.rotation;
    operator float*()             { return &m[0][0]; }
    operator const float*() const { return &m[0][0]; }

    // ── Column access ───────────────────────────────────────────────────
    Vector3 getColumn(int col) const {
        return Vector3(m[0][col], m[1][col], m[2][col]);
    }

    Vector3 getRow(int row) const {
        return Vector3(m[row][0], m[row][1], m[row][2]);
    }

    void setColumn(int col, const Vector3& v) {
        m[0][col] = v.x;
        m[1][col] = v.y;
        m[2][col] = v.z;
    }

    // ── Arithmetic ──────────────────────────────────────────────────────
    Matrix3 operator+(const Matrix3& o) const {
        Matrix3 r;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                r.m[i][j] = m[i][j] + o.m[i][j];
        return r;
    }

    Matrix3 operator-(const Matrix3& o) const {
        Matrix3 r;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                r.m[i][j] = m[i][j] - o.m[i][j];
        return r;
    }

    Matrix3 operator*(float s) const {
        Matrix3 r;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                r.m[i][j] = m[i][j] * s;
        return r;
    }

    Matrix3 operator/(float s) const {
        Matrix3 r;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                r.m[i][j] = m[i][j] / s;
        return r;
    }

    Matrix3& operator+=(const Matrix3& o) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m[i][j] += o.m[i][j];
        return *this;
    }

    Matrix3& operator-=(const Matrix3& o) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m[i][j] -= o.m[i][j];
        return *this;
    }

    Matrix3& operator*=(float s) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m[i][j] *= s;
        return *this;
    }

    // Matrix × Matrix. Matches SimBody.cpp's mulMatrixMatrixTranspose
    // and Math::momentToWorldSpace.
    Matrix3 operator*(const Matrix3& o) const {
        Matrix3 r;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                r.m[i][j] = m[i][0] * o.m[0][j]
                          + m[i][1] * o.m[1][j]
                          + m[i][2] * o.m[2][j];
            }
        }
        return r;
    }

    // Matrix × Vector3
    Vector3 operator*(const Vector3& v) const {
        return Vector3(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
        );
    }

    // ── Transpose / inverse ─────────────────────────────────────────────
    Matrix3 transpose() const {
        return Matrix3(
            m[0][0], m[1][0], m[2][0],
            m[0][1], m[1][1], m[2][1],
            m[0][2], m[1][2], m[2][2]
        );
    }

    float determinant() const {
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
             - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
             + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    Matrix3 inverse() const {
        float det = determinant();
        if (std::fabs(det) < 1e-12f) {
            return Matrix3::zero();
        }
        float invDet = 1.0f / det;

        Matrix3 r;
        r.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet;
        r.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invDet;
        r.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet;
        r.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invDet;
        r.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet;
        r.m[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * invDet;
        r.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invDet;
        r.m[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * invDet;
        r.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invDet;
        return r;
    }

    // ── Comparison ──────────────────────────────────────────────────────
    bool operator==(const Matrix3& o) const {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (m[i][j] != o.m[i][j]) return false;
        return true;
    }

    bool operator!=(const Matrix3& o) const { return !(*this == o); }

    bool fuzzyEq(const Matrix3& o, float tol) const {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (std::fabs(m[i][j] - o.m[i][j]) > tol) return false;
        return true;
    }

    // ── Methods needed by Math.cpp and util code ───────────────────────
    bool isOrthonormal() const {
        Matrix3 should_be_identity = (*this) * transpose();
        return should_be_identity.fuzzyEq(Matrix3::identity(), 1e-4f);
    }

    void orthonormalize() {
        // Gram-Schmidt on the columns.
        Vector3 c0 = getColumn(0);
        Vector3 c1 = getColumn(1);
        Vector3 c2 = getColumn(2);

        c0.unitize();
        c1 = (c1 - c0 * c0.dot(c1)).direction();
        c2 = c0.cross(c1);

        setColumn(0, c0);
        setColumn(1, c1);
        setColumn(2, c2);
    }

    static Matrix3 fromEulerAnglesXYZ(float x, float y, float z) {
        float cx = std::cos(x), sx = std::sin(x);
        float cy = std::cos(y), sy = std::sin(y);
        float cz = std::cos(z), sz = std::sin(z);

        Matrix3 rx(1, 0, 0,
                   0, cx, -sx,
                   0, sx, cx);
        Matrix3 ry(cy, 0, sy,
                   0, 1, 0,
                   -sy, 0, cy);
        Matrix3 rz(cz, -sz, 0,
                   sz, cz, 0,
                   0, 0, 1);

        return rx * ry * rz;
    }
};

// ── Free functions ──────────────────────────────────────────────────────
inline Matrix3 operator*(float s, const Matrix3& a) { return a * s; }

inline Matrix3 transpose(const Matrix3& a) { return a.transpose(); }
inline float determinant(const Matrix3& a) { return a.determinant(); }
inline Matrix3 inverse(const Matrix3& a) { return a.inverse(); }

// Left-multiply: v * M, which is v^T * M (row-vector times matrix).
// Used by Math::vectorToObjectSpace and Extents::express.
inline Vector3 operator*(const Vector3& v, const Matrix3& m) {
    return Vector3(
        v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0],
        v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1],
        v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2]
    );
}

} // namespace G3D