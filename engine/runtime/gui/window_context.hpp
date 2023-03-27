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
protected:
    using on_reset_fn        = std::function<void()>;
    using on_key_fn          = std::function<void(int, int, int, int)>;
    using on_char_fn         = std::function<void(unsigned int)>;
    using on_char_mods_fn    = std::function<void(int, unsigned int)>;
    using on_mouse_button_fn = std::function<void(int, int, int)>;
    using on_cursor_pos_fn   = std::function<void(double, double)>;
    using on_cursor_enter_fn = std::function<void(int)>;
    using on_scroll_fn       = std::function<void(double, double)>;
    using on_drop_fn         = std::function<void(int, const char**)>;
    using on_window_size_fn  = std::function<void(int, int)>;
    using on_window_close_fn = std::function<void()>;

    static void keyCallback(GLFWwindow* window, int key, int scancode,
                            int action, int mods) {}
    static void charCallback(GLFWwindow* window, unsigned int codepoint) {}
    static void charModsCallback(GLFWwindow* window, unsigned int codepoint,
                                 int mods) {}
    static void mouseButtonCallback(GLFWwindow* window, int button, int action,
                                    int mods) {}
    static void cursorPosCallback(GLFWwindow* window, double xpos,
                                  double ypos) {}
    static void cursorEnterCallback(GLFWwindow* window, int entered) {}
    static void scrollCallback(GLFWwindow* window, double xoffset,
                               double yoffset) {}
    static void dropCallback(GLFWwindow* window, int count,
                             const char** paths) {}
    static void windowSizeCallback(GLFWwindow* window, int width, int height) {}
    static void windowCloseCallback(GLFWwindow* window) {
        glfwSetWindowShouldClose(window, true);
    }

public:
    std::int32_t width{0};
    std::int32_t height{0};

    std::string_view title{};

    bool is_vsync{false};

    static void errorCallBack(int error, const char* description) {
        spdlog::error("GLFW Error: {}, {}", error, description);
    }
};

}// namespace taixu

#endif//TAIXUENGINE_WINDOW_CONTEXT_HPP
