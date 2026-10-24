#pragma once

#include <mutex>

namespace boost {

class mutex {
public:
    mutex() = default;
    ~mutex() = default;

    mutex(const mutex&) = delete;
    mutex& operator=(const mutex&) = delete;

    void lock()   { m.lock(); }
    void unlock() { m.unlock(); }
    bool try_lock() { return m.try_lock(); }

    typedef std::unique_lock<mutex> scoped_lock;

private:
    std::mutex m;
};

} // namespace boost