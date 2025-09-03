//
// Created by xmmmmmovo on 11/13/2023.
//

#pragma once

#include <taixu/common/base/macro.hpp>

#include <fmt/core.h>
#include <fmt/format.h>
#include <quill/LogMacros.h>
#include <quill/Logger.h>

namespace taixu {

// NOLINTBEGIN

/**
 * @brief Debug leve log
 *
 */
#define DEBUG_LOG(...) LOG_DEBUG(Logger::getLogger(), __VA_ARGS__)

/**
 * @brief Info leve log
 *
 */
#define INFO_LOG(...) LOG_INFO(Logger::getLogger(), __VA_ARGS__)

/**
 * @brief Warning leve log
 *
 */
#define WARN_LOG(...) LOG_WARN(Logger::getLogger(), __VA_ARGS__)

/**
 * @brief Error leve log
 *
 */
#define ERROR_LOG(...) LOG_ERROR(Logger::getLogger(), __VA_ARGS__)

/**
 * @brief Fatal leve log
 *
 */
#define FATAL_LOG(...)                                                                                                 \
    LOG_CRITIAL(Logger::getLogger(), __VA_ARGS__);                                                                     \
    { fatalError(__VA_ARGS__); }

// NOLINTEND

struct FileSinkConfiguration {
    std::filesystem::path log_file_path;
};

struct ConsoleSinkConfiguration {
    bool is_coloured{true};
};

struct LogConfiguration {
    std::optional<ConsoleSinkConfiguration> console_sink_config{std::nullopt};
    std::optional<FileSinkConfiguration>    file_sink_config{std::nullopt};
};

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
        DEBUG = static_cast<uint8_t>(quill::LogLevel::Debug),
        INFO  = static_cast<uint8_t>(quill::LogLevel::Info),
        WARN  = static_cast<uint8_t>(quill::LogLevel::Warning),
        ERR   = static_cast<uint8_t>(quill::LogLevel::Error),
        FATAL = static_cast<uint8_t>(quill::LogLevel::Critical),
    };

public:
    /**
     * @brief
     *
     */
    static void init(LogConfiguration const& config);
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
     * @brief Throw fatal error.
     * @exception std::runtime_error unknow error throw when fatal error occurs.
     * @param fmt
     * @param args
     */
    template<typename... TArgs>
    static void fatalError(fmt::format_string<TArgs...> const& fmt, TArgs&&... args) {
        throw std::runtime_error(fmt::format(fmt, std::forward<TArgs>(args)...));
    }

    /**
     * @brief Throw fatal error.
     * @exception std::runtime_error unknow error throw when fatal error occurs.
     * @param msg Throw error message
     */
    static void fatalError(std::basic_string_view<char> const& msg) {
        throw std::runtime_error(msg.data());
    }

    static quill::Logger* getLogger() {
        return logger;
    }

private:
    Logger() = default;

    /**
     * @brief
     *
     */
    TX_INLINE static quill::Logger* logger;
};

}// namespace taixu
