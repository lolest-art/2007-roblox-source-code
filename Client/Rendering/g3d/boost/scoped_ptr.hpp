#pragma once

#include <memory>

namespace boost {

template<class T>
class scoped_ptr {
public:
    explicit scoped_ptr(T* p = nullptr) : p_(p) {}
    ~scoped_ptr() { delete p_; }

    scoped_ptr(scoped_ptr&& o) noexcept : p_(o.p_) { o.p_ = nullptr; }
    scoped_ptr& operator=(scoped_ptr&& o) noexcept {
        if (this != &o) { delete p_; p_ = o.p_; o.p_ = nullptr; }
        return *this;
    }
    scoped_ptr(const scoped_ptr&) = delete;
    scoped_ptr& operator=(const scoped_ptr&) = delete;

    T& operator*() const  { return *p_; }
    T* operator->() const { return p_; }
    T* get() const        { return p_; }
    T* release()          { T* p = p_; p_ = nullptr; return p; }
    void reset(T* p = nullptr) { if (p != p_) { delete p_; p_ = p; } }
    void swap(scoped_ptr& o) { std::swap(p_, o.p_); }
    operator bool() const { return p_ != nullptr; }

private:
    T* p_;
};

template<class T>
class scoped_array {
public:
    explicit scoped_array(T* p = nullptr) : p_(p) {}
    ~scoped_array() { delete[] p_; }
    scoped_array(const scoped_array&) = delete;
    scoped_array& operator=(const scoped_array&) = delete;
    T& operator[](std::size_t i) const { return p_[i]; }
    T* get() const { return p_; }
    void reset(T* p = nullptr) { if (p != p_) { delete[] p_; p_ = p; } }
private:
    T* p_;
};

} // namespace boost