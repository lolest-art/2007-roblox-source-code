#pragma once

#include <algorithm>

namespace G3D {

class Color3 {
public:
    float r, g, b;

    Color3() : r(0.0f), g(0.0f), b(0.0f) {}
    Color3(float r_, float g_, float b_) : r(r_), g(g_), b(b_) {}

    static const Color3& black()     { static Color3 c(0,   0,   0  ); return c; }
    static const Color3& white()     { static Color3 c(1,   1,   1  ); return c; }
    static const Color3& red()       { static Color3 c(1,   0,   0  ); return c; }
    static const Color3& green()     { static Color3 c(0,   1,   0  ); return c; }
    static const Color3& blue()      { static Color3 c(0,   0,   1  ); return c; }
    static const Color3& yellow()    { static Color3 c(1,   1,   0  ); return c; }
    static const Color3& cyan()      { static Color3 c(0,   1,   1  ); return c; }
    static const Color3& magenta()   { static Color3 c(1,   0,   1  ); return c; }
    static const Color3& gray()      { static Color3 c(0.5f, 0.5f, 0.5f); return c; }
    static const Color3& purple()    { static Color3 c(0.5f, 0.0f, 0.5f); return c; }
    static const Color3& orange()    { static Color3 c(1.0f, 0.5f, 0.0f); return c; }

    Color3 operator+(const Color3& o) const { return Color3(r + o.r, g + o.g, b + o.b); }
    Color3 operator-(const Color3& o) const { return Color3(r - o.r, g - o.g, b - o.b); }
    Color3 operator*(float s) const          { return Color3(r * s, g * s, b * s); }
    Color3 operator/(float s) const          { return Color3(r / s, g / s, b / s); }

    Color3& operator+=(const Color3& o) { r += o.r; g += o.g; b += o.b; return *this; }
    Color3& operator-=(const Color3& o) { r -= o.r; g -= o.g; b -= o.b; return *this; }
    Color3& operator*=(float s)          { r *= s;   g *= s;   b *= s;   return *this; }

    bool operator==(const Color3& o) const { return r == o.r && g == o.g && b == o.b; }
    bool operator!=(const Color3& o) const { return !(*this == o); }

    float sum() const { return r + g + b; }
    float average() const { return (r + g + b) / 3.0f; }

    Color3 clamp(float lo, float hi) const {
        return Color3(std::max(lo, std::min(r, hi)),
                      std::max(lo, std::min(g, hi)),
                      std::max(lo, std::min(b, hi)));
    }
};

inline Color3 operator*(float s, const Color3& c) { return c * s; }

} // namespace G3D