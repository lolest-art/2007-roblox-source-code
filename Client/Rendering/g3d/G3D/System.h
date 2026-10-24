#pragma once

#include <chrono>
#include <cstdint>

namespace G3D {

class System {
public:
    // Returns seconds elapsed since a fixed epoch (first call).
    // World.cpp uses this for profiling and throttling:
    //   double startTick = G3D::System::getTick();
    static double getTick() {
        using clock = std::chrono::steady_clock;
        static const auto start = clock::now();
        auto now = clock::now();
        return std::chrono::duration<double>(now - start).count();
    }

    // G3D also exposes getLocalTime, sleep, etc. Add only what the
    // physics build needs. Profiling.cpp uses getTick only.
};

typedef double RealTime;

} // namespace G3D