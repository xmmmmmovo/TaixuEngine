//
// Created by xmmmmmovo on 1/24/2024.
//

#include "common/base/cpu_clock.hpp"

namespace taixu {


float CpuClock::getDeltaTime() const { return delta_time; }

float CpuClock::getTimeSinceStart() const { return time_since_start; }

void CpuClock::reset() {
    start_time   = std::chrono::high_resolution_clock::now();
    last_time    = start_time;
    current_time = start_time;

    delta_time       = 0.0f;
    time_since_start = 0.0f;
}

void CpuClock::update() {
    last_time    = current_time;
    current_time = std::chrono::high_resolution_clock::now();
    elapsed_time = current_time - last_time;

    // TODO: time scale need to be proved
    delta_time = elapsed_time.count() * time_scale;
    time_since_start += delta_time;
}

float CpuClock::getFPS() const { return 1.0f / delta_time; }


}// namespace taixu