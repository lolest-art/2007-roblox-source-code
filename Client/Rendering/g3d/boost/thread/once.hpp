#pragma once

#include <mutex>

namespace boost {

typedef std::once_flag once_flag;

// Boost 1.34's BOOST_ONCE_INIT was a C-style initializer macro like {0}.
// With std::once_flag, the correct equivalent is a value-initialization.
// Using `once_flag flag = BOOST_ONCE_INIT;` at file scope must produce a
// valid object; `{}` does that.
#ifndef BOOST_ONCE_INIT
#define BOOST_ONCE_INIT {}
#endif

// Boost 1.34 argument order: call_once(function, flag)
inline void call_once(void (*func)(), once_flag& flag) {
    std::call_once(flag, func);
}

// Forward overload for arbitrary functors — some code uses this order.
template<typename Func>
inline void call_once(once_flag& flag, Func f) {
    std::call_once(flag, f);
}

} // namespace boost