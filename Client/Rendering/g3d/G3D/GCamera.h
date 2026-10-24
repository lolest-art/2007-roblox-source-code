#pragma once

#include "Vector3.h"
#include "Plane.h"
#include "Array.h"

namespace G3D {

// Stub. The physics kernel never calls these methods; the header just
// needs to parse so util/Extents.h and util/Math.h compile.
class GCamera {
public:
    struct Frustum {
        struct Face {
            Plane plane;
        };
        Array<Face> faceArray;

        bool contains(const Vector3&) const { return true; }
    };

    Frustum frustum;
};

} // namespace G3D