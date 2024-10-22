//
// Created by xmmmmmovo on 11/14/2023.
//

#ifndef ENGINE_SRC_COMMON_EXCEPTION_RUNTIME_ERROR_0EF1CDE37B224C2C93D44F43505DAA86
#define ENGINE_SRC_COMMON_EXCEPTION_RUNTIME_ERROR_0EF1CDE37B224C2C93D44F43505DAA86

#include <format>
#include <stdexcept>

namespace taixu {

class TXRuntimeError : public std::runtime_error {
private:
    tx_string _err_msg{};

public:
    template<typename... Args>
    explicit TXRuntimeError(const tx_string& message, Args... args) : std::runtime_error(message) {
        _err_msg = std::format(message, args...);
    }

    char const* what() const noexcept override { return _err_msg.c_str(); }
};

}// namespace taixu

#endif// ENGINE_SRC_COMMON_EXCEPTION_RUNTIME_ERROR_0EF1CDE37B224C2C93D44F43505DAA86
