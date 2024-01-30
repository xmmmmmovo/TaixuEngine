//
// Created by xmmmmmovo on 2023/2/27.
//

#ifndef TAIXUENGINE_NOTIMPLEMENTED_EXCEPTION_HPP
#define TAIXUENGINE_NOTIMPLEMENTED_EXCEPTION_HPP

#include <stdexcept>

#define NOT_IMPL_ASSERT() assert(false && "Not implemented!");

namespace taixu {

class NotImplementedException final : public std::logic_error {
public:
    explicit NotImplementedException(const std::string& _Message)
        : logic_error(_Message) {}
    explicit NotImplementedException(const char* _Message)
        : logic_error(_Message) {}
    [[nodiscard]] char const* what() const noexcept override {
        return "Function not yet implemented.";
    }
};

}// namespace taixu

#endif// TAIXUENGINE_NOTIMPLEMENTED_EXCEPTION_HPP
