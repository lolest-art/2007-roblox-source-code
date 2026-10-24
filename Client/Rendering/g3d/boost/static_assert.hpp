#pragma once

#define BOOST_STATIC_ASSERT(expr) static_assert(expr, #expr)
#define BOOST_STATIC_ASSERT_MSG(expr, msg) static_assert(expr, msg)