#pragma once

namespace boost {

template<typename T>
class thread_specific_ptr {
public:
    thread_specific_ptr() = default;
    ~thread_specific_ptr() { delete ptr_; }

    T* get() const { return ptr_; }
    T* operator->() const { return ptr_; }
    T& operator*()  const { return *ptr_; }

    T* release() { T* p = ptr_; ptr_ = nullptr; return p; }

    void reset(T* p = nullptr) {
        if (p != ptr_) {
            delete ptr_;
            ptr_ = p;
        }
    }

private:
    thread_specific_ptr(const thread_specific_ptr&) = delete;
    thread_specific_ptr& operator=(const thread_specific_ptr&) = delete;

    static thread_local T* ptr_;
};

template<typename T>
thread_local T* thread_specific_ptr<T>::ptr_ = nullptr;

} // namespace boost