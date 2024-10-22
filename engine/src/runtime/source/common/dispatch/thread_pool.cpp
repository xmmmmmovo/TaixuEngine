//
// Created by xmmmmmovo on 2023/5/5.
//

#include "thread_pool.hpp"

namespace taixu {

void ThreadPool::createThreads(std::size_t thread_count) {
    for (size_t i = 0; i < thread_count; ++i) {
        _threads.emplace_back([this] {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->_mutex);
                    this->_cv.wait(lock, [this] { return this->_stop || !this->_tasks.empty(); });

                    if (this->_stop && this->_tasks.empty()) {
                        return;
                    }

                    task = std::move(this->_tasks.front());
                    this->_tasks.pop();
                }

                task();
            }
        });
    }
}

void ThreadPool::destroyThreads() {
    {
        std::unique_lock<std::mutex> const lock(_mutex);
        _stop = true;
    }

    _cv.notify_all();

    for (auto& thread : _threads) {
        thread.join();
    }
}

}// namespace taixu
