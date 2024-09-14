//
// Created by xmmmmmovo on 11/13/2023.
//

#include <taixu/common/log/logger.hpp>

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace taixu {

void Logger::init() {
    constexpr uint32_t SIZE = 8192;

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("%^[%l] [%! line:%#] %v %$");

    const spdlog::sinks_init_list sink_list = {console_sink};

    spdlog::init_thread_pool(SIZE, 1);

    logger = std::make_shared<spdlog::async_logger>("muggle_logger", sink_list.begin(), sink_list.end(),
                                                    spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    logger->set_level(spdlog::level::trace);

    spdlog::register_logger(logger);
}

void Logger::destroy() {
    logger->flush();
    spdlog::drop_all();
}

void Logger::setLevel(Logger::LogLevel level) {
    logger->set_level(static_cast<spdlog::level::level_enum>(level));
}

}// namespace taixu
