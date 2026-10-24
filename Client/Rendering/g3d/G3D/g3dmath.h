#pragma once
#include "g3dtypes.h"
#include <cmath>
#include <algorithm>
#include <limits>

namespace G3D {

// G3D rounds to nearest, ties away from zero.
// Constants.cpp relies on: G3D::iRound(0.5) == 1
inline int iRound(double x)  { return static_cast<int>(std::floor(x + 0.5)); }
inline int iRound(float x)   { return static_cast<int>(std::floor(x + 0.5f)); }
// Scalar min/max — G3D provides these as free functions.
inline float  min(float  a, float  b) { return std::min(a, b); }
inline float  max(float  a, float  b) { return std::max(a, b); }
inline double min(double a, double b) { return std::min(a, b); }
inline double max(double a, double b) { return std::max(a, b); }
inline int    min(int    a, int    b) { return std::min(a, b); }
inline int    max(int    a, int    b) { return std::max(a, b); }
inline int iFloor(float x) { return static_cast<int>(std::floor(x)); }
inline int iCeil(float x)  { return static_cast<int>(std::ceil(x)); }

inline float square(float x) { return x * x; }
inline float rsqrt(float x)  { return 1.0f / std::sqrt(x); }

// Angles
inline float pi()     { return 3.14159265358979323846f; }
inline float inf()  { return std::numeric_limits<float>::infinity(); }
inline float nan()  { return std::numeric_limits<float>::quiet_NaN(); }
inline float halfPi() { return 1.57079632679489661923f; }
inline float twoPi()  { return 6.28318530717958647692f; }

inline float degreesToRadians(float d) { return d * (pi() / 180.0f); }
inline float radiansToDegrees(float r) { return r * (180.0f / pi()); }

// Scalar helpers
template<typename T>
inline T clamp(T x, T lo, T hi) { return std::max(lo, std::min(x, hi)); }

template<typename T>
inline T sign(T x) { return (T(0) < x) - (x < T(0)); }

inline float lerp(float a, float b, float t) { return a + (b - a) * t; }

// Generic min/max — works for any type with operator<.
// This is how G3D's real min/max work: they're templates.
template<typename T>
inline const T& min(const T& a, const T& b) { return b < a ? b : a; }

template<typename T>
inline const T& max(const T& a, const T& b) { return a < b ? b : a; }

} // namespace G3D