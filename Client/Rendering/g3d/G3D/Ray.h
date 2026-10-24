#pragma once

#include "Vector3.h"

namespace G3D {

class Ray {
public:
    Vector3 origin;
    Vector3 direction;

    Ray() : origin(0, 0, 0), direction(0, 0, 1) {}
    Ray(const Vector3& o, const Vector3& d) : origin(o), direction(d) {}

    static Ray fromOriginAndDirection(const Vector3& o, const Vector3& d) {
        return Ray(o, d);
    }

    Ray unit() const {
        return Ray(origin, direction.unit());
    }

    Vector3 pointAt(float t) const {
        return origin + direction * t;
    }
};

} // namespace G3D