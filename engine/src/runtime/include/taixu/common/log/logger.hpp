//
// Created by xmmmmmovo on 11/13/2023.
//

#ifndef ENGINE_SRC_COMMON_LOG_LOGGER_E9C1FBD2F1524E5A81CDE784368C4FA4
#define ENGINE_SRC_COMMON_LOG_LOGGER_E9C1FBD2F1524E5A81CDE784368C4FA4

#include <taixu/common/base/macro.hpp>

#include <fmt/core.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

namespace taixu {

using source_loc_t = spdlog::source_loc;

#define LOG_SOURCE_LOC                                                                                                 \
    spdlog::source_loc {                                                                                               \
        __FILE__, __LINE__, __FUNCTION__                                                                               \
    }

// NOLINTBEGIN

/**
 * @brief Debug leve log
 *
 */
#define DEBUG_LOG(...) Logger::log(LOG_SOURCE_LOC, Logger::LogLevel::DEBUG, __VA_ARGS__)

/**
 * @brief Info leve log
 *
 */
#define INFO_LOG(...) Logger::log(LOG_SOURCE_LOC, Logger::LogLevel::INFO, __VA_ARGS__)

/**
 * @brief Warning leve log
 *
 */
#define WARN_LOG(...) Logger::log(LOG_SOURCE_LOC, Logger::LogLevel::WARN, __VA_ARGS__)

/**
 * @brief Error leve log
 *
 */
#define ERROR_LOG(...) Logger::log(LOG_SOURCE_LOC, Logger::LogLevel::ERR, __VA_ARGS__)

/**
 * @brief Fatal leve log
 *
 */
#define FATAL_LOG(...) Logger::log(LOG_SOURCE_LOC, Logger::LogLevel::FATAL, __VA_ARGS__)

/**
 * @brief Debug leve log with custom source location
 *
 */
#define DEBUG_LOG_LOC(source_loc, ...) Logger::log(std::move(source_loc), Logger::LogLevel::DEBUG, __VA_ARGS__)

/**
 * @brief Info leve log with custom source location
 *
 */
#define INFO_LOG_LOC(source_loc, ...) Logger::log(std::move(source_loc), Logger::LogLevel::INFO, __VA_ARGS__)

/**
 * @brief Warning leve log with custom source location
 *
 */
#define WARN_LOG_LOC(source_loc, ...) Logger::log(std::move(source_loc), Logger::LogLevel::WARN, __VA_ARGS__)

/**
 * @brief Error leve log with custom source location
 *
 */
#define ERROR_LOG_LOC(source_loc, ...) Logger::log(std::move(source_loc), Logger::LogLevel::ERR, __VA_ARGS__)

/**
 * @brief Fatal leve log with custom source location
 *
 */
#define FATAL_LOG_LOC(source_loc, ...) Logger::log(std::move(source_loc), Logger::LogLevel::FATAL, __VA_ARGS__)

// NOLINTEND

/**
 * @brief Logger class for logging runtime messages
 *
 */
class Logger final {
public:
    /**
     * @brief Logging Levels
     *
     */
    enum class LogLevel : uint8_t {
        DEBUG = spdlog::level::debug,
        INFO  = spdlog::level::info,
        WARN  = spdlog::level::warn,
        ERR   = spdlog::level::err,
        FATAL = spdlog::level::critical,
    };

public:
    /**
     * @brief
     *
     */
    static void init();
    /**
     * @brief
     *
     */
    static void destroy();
    /**
     * @brief Set the Logging Level.
     *
     * @param level @ref LogLevel
     */
    static void setLevel(LogLevel level);

    /**
     * @brief
     *
     * @param loc
     * @param level
     * @param msg
     */
    static void log(spdlog::source_loc const&& loc, LogLevel level, std::string_view const& msg) {
        logger->log(loc, static_cast<spdlog::level::level_enum>(level), msg);
        if (level == LogLevel::FATAL) {
            fatalError(msg);
        }
    }

    /**
     * @brief
     *
     * @tparam TArgs
     * @param loc
     * @param level
     * @param fmt
     * @param args
     */
    template<typename... TArgs>
    static void log(spdlog::source_loc const&& loc, LogLevel level, fmt::format_string<TArgs...> const& fmt,
                    TArgs&&... args) {
        logger->log(loc, static_cast<spdlog::level::level_enum>(level), fmt, std::forward<TArgs>(args)...);
        if (level == LogLevel::FATAL) {
            const std::string format_str = fmt::format(fmt, std::forward<TArgs>(args)...);
            fatalError(format_str);
        }
    }

    /**
     * @brief Throw fatal error.
     * @exception std::runtime_error unknow error throw when fatal error occurs.
     * @param msg Throw error message
     */
    static void fatalError(std::basic_string_view<char> const& msg) {
        throw std::runtime_error(msg.data());
    }

private:
    Logger() = default;

    /**
     * @brief
     *
     */
    TX_INLINE static std::shared_ptr<spdlog::logger> logger;
};

}// namespace taixu

#endif// ENGINE_SRC_COMMON_LOG_LOGGER_E9C1FBD2F1524E5A81CDE784368C4FA4
