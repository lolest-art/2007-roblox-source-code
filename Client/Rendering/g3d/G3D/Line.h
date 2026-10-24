#pragma once

#include "Vector3.h"
#include "Plane.h"
#include <cmath>

namespace G3D {

class Line {
public:
    Vector3 point;
    Vector3 direction;

    Line() : point(0, 0, 0), direction(0, 0, 1) {}
    Line(const Vector3& p, const Vector3& d) : point(p), direction(d) {}

    static Line fromPointAndDirection(const Vector3& p, const Vector3& d) {
        return Line(p, d);
    }

    Vector3 intersection(const Plane& plane) const {
        float denom = direction.dot(plane.normal());
        if (std::fabs(denom) < 1e-9f) {
            return Vector3::inf();
        }
        float t = -(plane.normal().dot(point) + plane.distance()) / denom;
        return point + direction * t;
    }
};

} // namespace G3D