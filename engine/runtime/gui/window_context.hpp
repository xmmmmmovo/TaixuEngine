//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_WINDOW_CONTEXT_HPP
#define TAIXUENGINE_WINDOW_CONTEXT_HPP

#include <string>

namespace taixu {

/**
 * @brief 仅在父类使用为Prop 在所有类中使用为Context
 */
class IWindowContext {
public:
    std::int32_t width{0};
    std::int32_t height{0};

    std::string_view title{};
};

}// namespace taixu

#endif//TAIXUENGINE_WINDOW_CONTEXT_HPP
