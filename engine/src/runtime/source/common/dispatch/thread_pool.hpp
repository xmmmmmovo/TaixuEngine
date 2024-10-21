//
// Created by xmmmmmovo on 2023/5/5.
//

#ifndef ENGINE_RUNTIME_CORE_DISPATCH_THREAD_POOL_HPP
#define ENGINE_RUNTIME_CORE_DISPATCH_THREAD_POOL_HPP

#include <cstddef>
#include <future>
#include <mutex>
#include <queue>

namespace taixu {

/**
 * @brief 线程池 C++17 Version
 */
class ThreadPool {
private:
    std::vector<std::thread>          _threads;
    std::queue<std::function<void()>> _tasks;

    std::mutex              _mutex;
    std::condition_variable _cv;

    bool _stop{false};

private:
    void createThreads(std::size_t thread_count = 0);

    void destroyThreads();

public:
    explicit ThreadPool(size_t thread_count = 0) {
        if (thread_count == 0) {
            thread_count = std::thread::hardware_concurrency();
        }
        createThreads(thread_count);
    }

    ~ThreadPool() {
        waitForTasks();
        destroyThreads();
    }

    template<typename F, typename... Args>
    void enqueue(F&& f, Args&&... args) {
        {
            std::unique_lock<std::mutex> const lock(_mutex);

            _tasks.emplace([f, args...]() { f(args...); });
        }

        _cv.notify_one();
    }

    void waitForTasks() {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [this] { return this->_tasks.empty(); });
    }

    void clear() {
        std::unique_lock<std::mutex> const lock(_mutex);
        while (!_tasks.empty()) {
            _tasks.pop();
        }
    }

    size_t size() {
        std::unique_lock<std::mutex> const lock(_mutex);
        return _tasks.size();
    }

    bool empty() {
        std::unique_lock<std::mutex> const lock(_mutex);
        return _tasks.empty();
    }

    void stop() {
        std::unique_lock<std::mutex> const lock(_mutex);
        _stop = true;
    }

    void start() {
        std::unique_lock<std::mutex> const lock(_mutex);
        _stop = false;
    }

    void wait_for(std::chrono::milliseconds ms) {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait_for(lock, ms);
    }
};

}// namespace taixu

#endif// ENGINE_RUNTIME_CORE_DISPATCH_THREAD_POOL_HPP
