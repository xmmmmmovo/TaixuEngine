//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_WINDOW_PROP_HPP
#define TAIXUENGINE_WINDOW_PROP_HPP

namespace taixu::gui {

/**
 * @brief 仅在父类使用为Prop 在子类使用为Context
 */
struct IWindowProp {
    std::int32_t width{0};
    std::int32_t height{0};

    std::string_view title{};
    explicit IWindowProp() = default;
    explicit IWindowProp(std::int32_t const &width, std::int32_t const &height,
                         std::string_view const &title)
        : width(width), height(height), title(title) {}
};

}// namespace taixu::gui

#endif//TAIXUENGINE_WINDOW_PROP_HPP
