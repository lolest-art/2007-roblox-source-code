#pragma once

#include <memory>

namespace boost {
    using std::shared_ptr;
    using std::weak_ptr;
    using std::static_pointer_cast;
    using std::dynamic_pointer_cast;
    using std::const_pointer_cast;
    using std::make_shared;
    using std::enable_shared_from_this;

    // boost 1.34's legacy cast names — some code uses these.
    template<class T, class U>
    inline shared_ptr<T> shared_static_cast(const shared_ptr<U>& p) {
        return std::static_pointer_cast<T>(p);
    }
    template<class T, class U>
    inline shared_ptr<T> shared_dynamic_cast(const shared_ptr<U>& p) {
        return std::dynamic_pointer_cast<T>(p);
    }
    template<class T, class U>
    inline shared_ptr<T> shared_polymorphic_downcast(const shared_ptr<U>& p) {
        return std::static_pointer_cast<T>(p);
    }
}