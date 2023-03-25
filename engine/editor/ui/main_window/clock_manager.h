#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

#include <chrono>
#include <functional>
#include <memory>
#include <unordered_map>

class Clock {
public:
    using TimePoint = std::chrono::high_resolution_clock::time_point;

public:
    Clock() = default;

    void reset() {
        m_startTime = std::chrono::high_resolution_clock::now();
    }

    double getCurrentTime() const {
        TimePoint now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = now - m_startTime;
        return duration.count();
    }

private:
    TimePoint m_startTime{std::chrono::high_resolution_clock::now()};
};

class ClockManager {
public:
    static ClockManager &getInstance() {
        static ClockManager instance;
        return instance;
    }

    Clock &getClock(const std::string &name) {
        if (m_clocks.find(name) == m_clocks.end()) {
            m_clocks.emplace(name, std::make_unique<Clock>());
        }
        return *(m_clocks[name]);
    }

private:
    ClockManager() = default;

private:
    std::unordered_map<std::string, std::unique_ptr<Clock>> m_clocks;
};

#endif // CLOCK_MANAGER_H
