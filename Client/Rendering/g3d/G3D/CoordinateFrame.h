#pragma once

#include "Vector3.h"
#include "Matrix3.h"
#include "Ray.h"

namespace G3D {

class CoordinateFrame {
public:
    Matrix3 rotation;
    Vector3 translation;

    CoordinateFrame()
        : rotation(Matrix3::identity()), translation(0, 0, 0) {}

    CoordinateFrame(const Matrix3& r, const Vector3& t)
        : rotation(r), translation(t) {}

    // Rotation-only constructor. Math::setHeadingElevation uses:
    //   G3D::CoordinateFrame cf(focus.rotation);
    explicit CoordinateFrame(const Matrix3& r)
        : rotation(r), translation(0, 0, 0) {}

    explicit CoordinateFrame(const Vector3& t)
        : rotation(Matrix3::identity()), translation(t) {}

    static const CoordinateFrame& identity() {
        static CoordinateFrame cf;
        return cf;
    }

    static CoordinateFrame fromRotationTranslation(const Matrix3& r, const Vector3& t) {
        return CoordinateFrame(r, t);
    }

    CoordinateFrame operator*(const CoordinateFrame& o) const {
        return CoordinateFrame(rotation * o.rotation,
                               pointToWorldSpace(o.translation));
    }

    CoordinateFrame inverse() const {
        Matrix3 invRot = rotation.transpose();
        return CoordinateFrame(invRot, -(invRot * translation));
    }

    // ── Whole-frame transforms ──────────────────────────────────────────
    CoordinateFrame toWorldSpace(const CoordinateFrame& other) const {
        return (*this) * other;
    }

    CoordinateFrame toObjectSpace(const CoordinateFrame& other) const {
        return inverse() * other;
    }

    // ── Ray transforms ──────────────────────────────────────────────────
    Ray toWorldSpace(const Ray& ray) const {
        return Ray(pointToWorldSpace(ray.origin),
                   vectorToWorldSpace(ray.direction));
    }

    Ray toObjectSpace(const Ray& ray) const {
        return Ray(pointToObjectSpace(ray.origin),
                   vectorToObjectSpace(ray.direction));
    }

    // ── Point / vector transforms ───────────────────────────────────────
    Vector3 pointToWorldSpace(const Vector3& p) const {
        return rotation * p + translation;
    }

    Vector3 pointToObjectSpace(const Vector3& p) const {
        return rotation.transpose() * (p - translation);
    }

    Vector3 vectorToWorldSpace(const Vector3& v) const {
        return rotation * v;
    }

    Vector3 vectorToObjectSpace(const Vector3& v) const {
        return rotation.transpose() * v;
    }

    Vector3 lookVector() const   { return -getColumn(2); }
    Vector3 getLookVector() const { return -getColumn(2); }

    void lookAt(const Vector3& target) {
        Vector3 look = (target - translation).direction();
        Vector3 right = look.cross(Vector3::unitY()).direction();
        Vector3 up = right.cross(look);
        setColumn(0, right);
        setColumn(1, up);
        setColumn(2, -look);
    }

    bool operator==(const CoordinateFrame& o) const {
        return rotation == o.rotation && translation == o.translation;
    }
    bool operator!=(const CoordinateFrame& o) const {
        return !(*this == o);
    }

    bool fuzzyEq(const CoordinateFrame& o, float tolT, float tolR) const {
        return translation.fuzzyEq(o.translation, tolT)
            && rotation.fuzzyEq(o.rotation, tolR);
    }

    Vector3 getColumn(int c) const { return rotation.getColumn(c); }
    void setColumn(int c, const Vector3& v) { rotation.setColumn(c, v); }

    const Matrix3& getRotation() const { return rotation; }
    const Vector3& getTranslation() const { return translation; }
};

} // namespace G3D