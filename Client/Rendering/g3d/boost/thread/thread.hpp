#pragma once

#include <thread>

namespace boost {

class thread {
public:
    thread() = default;

    template<typename Func>
    explicit thread(Func f) : t(f) {}

    thread(thread&&) = default;
    thread& operator=(thread&&) = default;

    void join() { t.join(); }
    bool joinable() const { return t.joinable(); }
    void detach() { t.detach(); }

private:
    std::thread t;
};

namespace this_thread {
    inline void yield() { std::this_thread::yield(); }
}

} // namespace boost