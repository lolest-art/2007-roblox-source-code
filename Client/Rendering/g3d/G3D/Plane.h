#pragma once

#include "Vector3.h"
#include <cmath>

namespace G3D {

class Plane {
public:
    Vector3 _normal;
    float   _distance;

    Plane() : _normal(0, 1, 0), _distance(0) {}

    Plane(const Vector3& normal, const Vector3& point)
        : _normal(normal), _distance(-normal.dot(point)) {}

    Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2) {
        _normal = (v1 - v0).cross(v2 - v0).direction();
        _distance = -_normal.dot(v0);
    }

    const Vector3& normal() const { return _normal; }
    float distance() const        { return _distance; }

    void getEquation(Vector3& n, double& d) const {
        n = _normal;
        d = _distance;
    }
    void getEquation(Vector3& n, float& d) const {
        n = _normal;
        d = _distance;
    }

    bool halfSpaceContains(const Vector3& p) const {
        return _normal.dot(p) + _distance >= 0.0f;
    }
};

} // namespace G3D