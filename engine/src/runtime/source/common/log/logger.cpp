//
// Created by xmmmmmovo on 11/13/2023.
//

#include "taixu/common/log/logger.hpp"

#include "quill/Backend.h"
#include "quill/Frontend.h"
#include "quill/Logger.h"
#include "quill/sinks/ConsoleSink.h"
#include "quill/sinks/FileSink.h"

namespace taixu {

void Logger::init(LogConfiguration const& config) {
    constexpr uint32_t SIZE = 8192;

    quill::BackendOptions backend_options;
    backend_options.thread_name = "Quill Log Thread";
    quill::Backend::start(backend_options);

    std::vector<std::shared_ptr<quill::Sink>> sinks;

    if (config.console_sink_config.has_value()) {
        auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("console_sink_1");
        sinks.emplace_back(std::move(console_sink));
    }

    if (config.file_sink_config.has_value()) {
        auto file_sink = quill::Frontend::create_or_get_sink<quill::FileSink>(
                "file_sink_1", config.file_sink_config->log_file_path, SIZE);
    }

    auto pattern = quill::PatternFormatterOptions{"%(time) [%(log_level:<9)] %(short_source_location:<12) %(message)"};
    logger       = quill::Frontend::create_or_get_logger("TaixuLogger", sinks);
    logger->set_log_level(quill::LogLevel::Info);
}

void Logger::destroy() {
    logger->flush_log();
    logger->mark_invalid();
}

void Logger::setLevel(Logger::LogLevel level) {
    logger->set_log_level(static_cast<quill::LogLevel>(level));
}

}// namespace taixu
