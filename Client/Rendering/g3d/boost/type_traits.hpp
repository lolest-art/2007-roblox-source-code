#pragma once
#include <type_traits>

namespace boost {
    using std::is_same;
    using std::is_base_of;
    using std::is_convertible;
    using std::enable_if;
    using std::enable_if_t;
    using std::conditional;
    using std::conditional_t;
    using std::remove_const;
    using std::remove_reference;
    using std::remove_pointer;
    using std::add_pointer;
    using std::is_pointer;
    using std::is_const;
    using std::is_reference;
}