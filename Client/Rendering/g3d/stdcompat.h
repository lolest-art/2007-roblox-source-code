#pragma once

// MSVC 14.5x removed std::binary_function and std::unary_function from
// <functional> entirely. Old C++03 code still uses them as base classes.
// Provide them only if <functional> hasn't already.

#include <functional>

#if !defined(_HAS_AUTO_PTR_ETC) || _HAS_AUTO_PTR_ETC == 0
    // <functional> didn't provide them; declare them ourselves.
    #ifndef RBX_STDCOMPAT_BINARY_FUNCTION_DEFINED
    #define RBX_STDCOMPAT_BINARY_FUNCTION_DEFINED

    namespace std {
        template<typename Arg1, typename Arg2, typename Result>
        struct binary_function {
            typedef Arg1   first_argument_type;
            typedef Arg2   second_argument_type;
            typedef Result result_type;
        };

        template<typename Arg, typename Result>
        struct unary_function {
            typedef Arg    argument_type;
            typedef Result result_type;
        };
    }

    #endif
#endif