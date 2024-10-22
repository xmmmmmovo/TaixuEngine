//
// Created by xmmmmmovo on 1/24/2024.
//

#include "taixu/common/base/cpu_clock.hpp"

TX_NAMESPACE_BEGIN

float CpuClock::getDeltaTime() const {
    return _delta_time;
}

float CpuClock::getTimeSinceStart() const {
    return _time_since_start;
}

void CpuClock::reset() {
    _start_time   = std::chrono::high_resolution_clock::now();
    _last_time    = _start_time;
    _current_time = _start_time;

    _delta_time       = 0.0f;
    _time_since_start = 0.0f;
}

void CpuClock::update() {
    _last_time    = _current_time;
    _current_time = std::chrono::high_resolution_clock::now();
    _elapsed_time = _current_time - _last_time;

    // TODO: time scale need to be proved
    _delta_time = _elapsed_time.count() * time_scale;
    _time_since_start += _delta_time;
}

float CpuClock::getFPS() const {
    return 1.0f / _delta_time;
}

TX_NAMESPACE_END
