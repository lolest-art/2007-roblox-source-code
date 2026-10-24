#pragma once
#include <functional>
#include <cstddef>

namespace boost {

template<typename T>
inline std::size_t hash_value(const T& v) {
    return std::hash<T>()(v);
}

} // namespace boost