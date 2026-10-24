#pragma once

#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>

namespace G3D {

// Minimal implementation of G3D's format() and vformat().
// Both take printf-style format strings and varargs.
// G3D's originals use a slightly different API but for the physics
// build these signatures satisfy all call sites.

inline std::string vformat(const char* fmt, va_list args) {
    va_list argsCopy;
    va_copy(argsCopy, args);
    int size = std::vsnprintf(nullptr, 0, fmt, argsCopy);
    va_end(argsCopy);

    if (size <= 0) {
        return std::string();
    }

    std::vector<char> buf(size + 1);
    std::vsnprintf(buf.data(), buf.size(), fmt, args);
    return std::string(buf.data(), size);
}

inline std::string format(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string result = vformat(fmt, args);
    va_end(args);
    return result;
}

} // namespace G3D