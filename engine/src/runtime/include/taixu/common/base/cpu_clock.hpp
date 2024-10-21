//
// Created by xmmmmmovo on 2023/3/2.
//

#pragma once

#include <chrono>

#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

class CpuClock {
private:
    std::chrono::high_resolution_clock::time_point _start_time;
    std::chrono::high_resolution_clock::time_point _last_time;
    std::chrono::high_resolution_clock::time_point _current_time;
    std::chrono::duration<float>                   _elapsed_time{};

    float _delta_time{};
    float _time_since_start{};

public:
    float time_scale{1.0f};

    [[nodiscard]] float getDeltaTime() const;
    [[nodiscard]] float getTimeSinceStart() const;

    void reset();

    void update();

    // calculate the fps
    [[nodiscard]] float getFPS() const;
};

TX_NAMESPACE_END
