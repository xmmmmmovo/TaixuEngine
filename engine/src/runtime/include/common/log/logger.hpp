//
// Created by xmmmmmovo on 11/13/2023.
//

#ifndef ENGINE_SRC_COMMON_LOG_LOGGER_E9C1FBD2F1524E5A81CDE784368C4FA4
#define ENGINE_SRC_COMMON_LOG_LOGGER_E9C1FBD2F1524E5A81CDE784368C4FA4

#include <common/base/macro.hpp>

#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

namespace taixu {

using source_loc_t = spdlog::source_loc;

#define LOG_SOURCE_LOC                                                         \
    spdlog::source_loc { __FILE__, __LINE__, __FUNCTION__ }

#define DEBUG_LOG(...)                                                         \
    Logger::log(LOG_SOURCE_LOC, Logger::LogLevel::DEBUG, __VA_ARGS__)

#define INFO_LOG(...)                                                          \
    Logger::log(LOG_SOURCE_LOC, Logger::LogLevel::INFO, __VA_ARGS__)

#define WARN_LOG(...)                                                          \
    Logger::log(LOG_SOURCE_LOC, Logger::LogLevel::WARN, __VA_ARGS__)

#define ERROR_LOG(...)                                                         \
    Logger::log(LOG_SOURCE_LOC, Logger::LogLevel::ERR, __VA_ARGS__)

#define FATAL_LOG(...)                                                         \
    Logger::log(LOG_SOURCE_LOC, Logger::LogLevel::FATAL, __VA_ARGS__)

#define DEBUG_LOG_LOC(source_loc, ...)                                         \
    Logger::log(std::move(source_loc), Logger::LogLevel::DEBUG, __VA_ARGS__)

#define INFO_LOG_LOC(source_loc, ...)                                          \
    Logger::log(std::move(source_loc), Logger::LogLevel::INFO, __VA_ARGS__)

#define WARN_LOG_LOC(source_loc, ...)                                          \
    Logger::log(std::move(source_loc), Logger::LogLevel::WARN, __VA_ARGS__)

#define ERROR_LOG_LOC(source_loc, ...)                                         \
    Logger::log(std::move(source_loc), Logger::LogLevel::ERR, __VA_ARGS__)

#define FATAL_LOG_LOC(source_loc, ...)                                         \
    Logger::log(std::move(source_loc), Logger::LogLevel::FATAL, __VA_ARGS__)

class Logger final {
public:
    enum class LogLevel : uint8_t {
        DEBUG = spdlog::level::debug,
        INFO  = spdlog::level::info,
        WARN  = spdlog::level::warn,
        ERR   = spdlog::level::err,
        FATAL = spdlog::level::critical,
    };

public:
    static void init();
    static void destroy();
    static void setLevel(LogLevel level);

    static void log(spdlog::source_loc const&& loc, LogLevel level,
                    std::string_view const& msg) {
        _logger->log(loc, static_cast<spdlog::level::level_enum>(level), msg);
        if (level == LogLevel::FATAL) { fatalError(msg); }
    }

    template<typename... TArgs>
    static void log(spdlog::source_loc const&& loc, LogLevel level,
                    fmt::format_string<TArgs...> const& fmt, TArgs&&... args) {
        _logger->log(loc, static_cast<spdlog::level::level_enum>(level), fmt,
                     std::forward<TArgs>(args)...);
        if (level == LogLevel::FATAL) {
            const std::string format_str =
                    fmt::format(fmt, std::forward<TArgs>(args)...);
            fatalError(format_str);
        }
    }

    static void fatalError(std::basic_string_view<char> const& msg) {
        throw std::runtime_error(msg.data());
    }

private:
     Logger() = default;
    ~Logger() = default;

    TX_INLINE static std::shared_ptr<spdlog::logger> _logger;
};


}// namespace taixu

#endif// ENGINE_SRC_COMMON_LOG_LOGGER_E9C1FBD2F1524E5A81CDE784368C4FA4
