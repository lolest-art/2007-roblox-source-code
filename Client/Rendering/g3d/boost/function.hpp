#pragma once
#include <functional>

namespace boost {
    using std::function;
    using std::bind;
    using std::ref;
    using std::cref;

    // Boost 1.34 uses boost::function0, function1, etc.
    template<typename R> using function0 = std::function<R()>;
    template<typename R, typename A1> using function1 = std::function<R(A1)>;
    template<typename R, typename A1, typename A2> using function2 = std::function<R(A1, A2)>;
}