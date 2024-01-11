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
    
    [[nodiscard]] float getDeltaTime() const { return delta_time; }
    [[nodiscard]] float getTimeSinceStart() const { return time_since_start; }

    void reset() {
        start_time   = std::chrono::high_resolution_clock::now();
        last_time    = start_time;
        current_time = start_time;

        delta_time       = 0.0f;
        time_since_start = 0.0f;
    }

    void update() {
        last_time    = current_time;
        current_time = std::chrono::high_resolution_clock::now();
        elapsed_time = current_time - last_time;

        // TODO: time scale need to be proved
        delta_time = elapsed_time.count() * time_scale;
        time_since_start += delta_time;
    }

    // calculate the fps
    [[nodiscard]] float getFPS() const { return 1.0f / delta_time; }
};

}// namespace taixu

#endif// TAIXUENGINE_CLOCK_HPP_7AAF21E5E5DB40FEA443453F3D77703A
