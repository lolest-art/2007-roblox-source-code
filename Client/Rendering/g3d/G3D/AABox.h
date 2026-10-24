#pragma once

#include "Vector3.h"
#include <algorithm>

namespace G3D {

class AABox {
public:
    Vector3 low;
    Vector3 high;

    AABox() : low(0, 0, 0), high(0, 0, 0) {}
    AABox(const Vector3& lo, const Vector3& hi) : low(lo), high(hi) {}

    Vector3 center() const { return (low + high) * 0.5f; }
    Vector3 extent() const { return high - low; }

    bool contains(const Vector3& p) const {
        return p.x >= low.x && p.x <= high.x
            && p.y >= low.y && p.y <= high.y
            && p.z >= low.z && p.z <= high.z;
    }

    bool overlapsOrTouches(const AABox& o) const {
        return !(high.x < o.low.x || o.high.x < low.x
              || high.y < o.low.y || o.high.y < low.y
              || high.z < o.low.z || o.high.z < low.z);
    }

    void unionWith(const AABox& o) {
        low  = low.min(o.low);
        high = high.max(o.high);
    }
};

} // namespace G3D