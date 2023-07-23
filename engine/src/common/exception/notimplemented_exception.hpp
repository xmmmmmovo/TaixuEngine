//
// Created by xmmmmmovo on 2023/2/27.
//

#ifndef TAIXUENGINE_NOTIMPLEMENTED_EXCEPTION_HPP
#define TAIXUENGINE_NOTIMPLEMENTED_EXCEPTION_HPP

#include <stdexcept>

namespace taixu {
class NotImplementedException : public std::logic_error {
public:
    [[nodiscard]] char const *what() const noexcept override {
        return "Function not yet implemented.";
    }
};
}// namespace taixu

#endif//TAIXUENGINE_NOTIMPLEMENTED_EXCEPTION_HPP
