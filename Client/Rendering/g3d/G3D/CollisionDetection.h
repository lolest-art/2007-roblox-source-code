#pragma once

#include "Vector3.h"
#include "AABox.h"
#include "Sphere.h"
#include <cmath>
#include <limits>
#include <algorithm>

namespace G3D {

class CollisionDetection {
public:
    // ── 4-argument overload: discards `inside` ──────────────────────────
    // SpatialHash.cpp uses this version.
    static bool collisionLocationForMovingPointFixedAABox(
        const Vector3& origin,
        const Vector3& direction,
        const AABox&   box,
        Vector3&       location)
    {
        bool inside;
        return collisionLocationForMovingPointFixedAABox(
            origin, direction, box, location, inside);
    }

    // ── 5-argument overload ─────────────────────────────────────────────
    // Block.cpp uses this version.
    //   returns true if hit, writes hit point into `location`
    //   sets `inside` to true if the ray origin is inside the box.
    static bool collisionLocationForMovingPointFixedAABox(
        const Vector3& origin,
        const Vector3& direction,
        const AABox&   box,
        Vector3&       location,
        bool&          inside)
    {
        float tmin = -std::numeric_limits<float>::infinity();
        float tmax =  std::numeric_limits<float>::infinity();

        inside = true;
        for (int i = 0; i < 3; ++i) {
            float o  = origin[i];
            float d  = direction[i];
            float lo = box.low[i];
            float hi = box.high[i];

            if (std::fabs(d) < 1e-12f) {
                if (o < lo || o > hi) return false;
            } else {
                float inv = 1.0f / d;
                float t1 = (lo - o) * inv;
                float t2 = (hi - o) * inv;
                if (t1 > t2) std::swap(t1, t2);
                if (t1 > tmin) tmin = t1;
                if (t2 < tmax) tmax = t2;
                if (tmin > tmax) return false;
            }

            if (o < lo || o > hi) inside = false;
        }

        float t = (tmin >= 0.0f) ? tmin : tmax;
        if (t < 0.0f) return false;

        location = origin + direction * t;
        return true;
    }

    // Quadratic solve — ray vs sphere.
    //   returns hit time or +inf on miss, writes hit point into `location`.
    static float collisionTimeForMovingPointFixedSphere(
        const Vector3& origin,
        const Vector3& direction,
        const Sphere&  sphere,
        Vector3&       location)
    {
        const float inf = std::numeric_limits<float>::infinity();

        Vector3 oc = origin - sphere.center;
        float a = direction.dot(direction);
        if (a <= 0.0f) return inf;

        float b = 2.0f * oc.dot(direction);
        float c = oc.dot(oc) - sphere.radius * sphere.radius;
        float disc = b * b - 4.0f * a * c;
        if (disc < 0.0f) return inf;

        float sq = std::sqrt(disc);
        float t = (-b - sq) / (2.0f * a);
        if (t < 0.0f) t = (-b + sq) / (2.0f * a);
        if (t < 0.0f) return inf;

        location = origin + direction * t;
        return t;
    }
};

} // namespace G3D