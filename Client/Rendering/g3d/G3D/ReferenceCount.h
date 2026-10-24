#pragma once

#include <atomic>

namespace G3D {

// Stub for G3D's ReferenceCountedObject. The v8 physics code uses
// boost::shared_ptr for ownership; this base class is vestigial and
// never actually invoked in the physics-only build. Provide a minimal
// implementation so headers that inherit from it compile.

class ReferenceCountedObject {
public:
    ReferenceCountedObject() : _refCount(1) {}
    virtual ~ReferenceCountedObject() {}

    void ReferenceCountedObject_ref() const { ++_refCount; }

    void ReferenceCountedObject_unref() const {
        if (--_refCount == 0) {
            delete const_cast<ReferenceCountedObject*>(this);
        }
    }

protected:
    // G3D's actual API is slightly different in different versions.
    // These aliases cover the common spellings.
    void reference() const { ReferenceCountedObject_ref(); }
    void unreference() const { ReferenceCountedObject_unref(); }

private:
    mutable std::atomic<int> _refCount;
};

// G3D also declares ReferenceCountedPointer<T>, a smart pointer that
// increments/decrements the refcount on construction/destruction.
// We implement it as a thin wrapper around std::shared_ptr-like
// semantics, but since nothing in the physics uses it, a trivial
// implementation is enough.

template<class T>
class ReferenceCountedPointer {
public:
    ReferenceCountedPointer() : _ptr(nullptr) {}
    ReferenceCountedPointer(T* p) : _ptr(p) { /* takes ownership */ }
    ~ReferenceCountedPointer() { /* nothing — stub */ }

    T* operator->() const { return _ptr; }
    T& operator*()  const { return *_ptr; }
    T* get()        const { return _ptr; }
    operator bool() const { return _ptr != nullptr; }

    // Comparison with nullptr — used in some code paths.
    bool operator==(std::nullptr_t) const { return _ptr == nullptr; }
    bool operator!=(std::nullptr_t) const { return _ptr != nullptr; }

private:
    T* _ptr;
};

} // namespace G3D