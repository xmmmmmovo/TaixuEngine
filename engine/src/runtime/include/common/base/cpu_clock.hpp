//
// Created by xmmmmmovo on 2023/3/2.
//

#ifndef TAIXUENGINE_CLOCK_HPP_7AAF21E5E5DB40FEA443453F3D77703A
#define TAIXUENGINE_CLOCK_HPP_7AAF21E5E5DB40FEA443453F3D77703A

#include <chrono>

namespace taixu {

class CpuClock {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point last_time;
    std::chrono::high_resolution_clock::time_point current_time;
    std::chrono::duration<float>                   elapsed_time{};

    float delta_time{};
    float time_since_start{};

public:
    float time_scale{1.0f};

    [[nodiscard]] float getDeltaTime() const;
    [[nodiscard]] float getTimeSinceStart() const;

    void reset();

    void update();

    // calculate the fps
    [[nodiscard]] float getFPS() const;
};

}// namespace taixu

#endif// TAIXUENGINE_CLOCK_HPP_7AAF21E5E5DB40FEA443453F3D77703A
