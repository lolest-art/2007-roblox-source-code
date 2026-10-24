#pragma once

#include "Vector3.h"

namespace G3D {

class Sphere {
public:
    Vector3 center;
    float   radius;

    Sphere() : center(0, 0, 0), radius(0) {}
    Sphere(const Vector3& c, float r) : center(c), radius(r) {}
};

} // namespace G3D