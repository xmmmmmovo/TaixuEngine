//
// Created by xmmmmmovo on 1/19/2024.
//
#include "taixu/gameplay/gui/window.hpp"

#include "taixu/common/base/macro.hpp"
#include "taixu/common/log/logger.hpp"

#include <backends/imgui_impl_glfw.h>

TX_NAMESPACE_BEGIN

Window::Window(WindowInfo const& window_info) : _window_info(window_info) {
}

void Window::update() {
    handleEvents();
}

RetCode Window::setTitle(std::string_view title) {
    _window_info.title = title;
    updateTitle(_window_info.title.data());
    return RetCode::SUCCESS;
}

TX_NAMESPACE_END
