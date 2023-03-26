//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_GLFW_WINDOW_HPP
#define TAIXUENGINE_GLFW_WINDOW_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

// "" headers
#include "window.hpp"

namespace taixu {

class TX_GLFWwindow {
protected:
    GLFWwindow *window{nullptr};
    bool        initialized{false};
    bool        is_vsync{false};

private:
    using on_reset_fn        = std::function<void()>;
    using on_key_fn          = std::function<void(int, int, int, int)>;
    using on_char_fn         = std::function<void(unsigned int)>;
    using on_char_mods_fn    = std::function<void(int, unsigned int)>;
    using on_mouse_button_fn = std::function<void(int, int, int)>;
    using on_cursor_pos_fn   = std::function<void(double, double)>;
    using on_cursor_enter_fn = std::function<void(int)>;
    using on_scroll_fn       = std::function<void(double, double)>;
    using on_drop_fn         = std::function<void(int, const char **)>;
    using on_window_size_fn  = std::function<void(int, int)>;
    using on_window_close_fn = std::function<void()>;

    static void errorCallBack(int error, const char *description);

public:
    TX_GLFWwindow()  = default;
    ~TX_GLFWwindow() = default;

    void init(IWindowContext *context);
    void update();
    void destroy();

    [[nodiscard]] bool shouldClose() const;

    [[nodiscard]] bool getIsVsync() const;
    void               setIsVsync(bool isVsync);
};

}// namespace taixu

#endif//TAIXUENGINE_GLFW_WINDOW_HPP
