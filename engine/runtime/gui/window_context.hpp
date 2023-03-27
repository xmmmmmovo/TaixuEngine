//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_WINDOW_CONTEXT_HPP
#define TAIXUENGINE_WINDOW_CONTEXT_HPP


#include <GLFW/glfw3.h>

#include <string>

#include "core/base/macro.hpp"

namespace taixu {
/**
 * @brief 仅在父类使用为Prop 在所有类中使用为Context
 */
class WindowContext {
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

    std::vector<on_reset_fn>        on_reset_fns;
    std::vector<on_key_fn>          on_key_fns;
    std::vector<on_char_fn>         on_char_fns;
    std::vector<on_char_mods_fn>    on_char_mods_fns;
    std::vector<on_mouse_button_fn> on_mouse_button_fns;
    std::vector<on_cursor_pos_fn>   on_cursor_pos_fns;
    std::vector<on_cursor_enter_fn> on_cursor_enter_fns;
    std::vector<on_scroll_fn>       on_scroll_fns;
    std::vector<on_drop_fn>         on_drop_fns;
    std::vector<on_window_size_fn>  on_window_size_fns;
    std::vector<on_window_close_fn> on_window_close_fns;

    static void errorCallBack(int error, const char* description) {
        spdlog::error("GLFW Error: {}, {}", error, description);
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode,
                            int action, int mods) {
        auto* context =
                static_cast<WindowContext*>(glfwGetWindowUserPointer(window));
        context->onKey(key, scancode, action, mods);
    }
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

    void onKey(int key, int scancode, int action, int mods) {
        for (auto const& func : on_key_fns) {
            func(key, scancode, action, mods);
        }
    }

public:
    GLFWwindow* _window{nullptr};

    std::int32_t _width{0};
    std::int32_t _height{0};

    std::string_view _title{};

    /**
     * @brief editor state
     */
    EngineState state{EngineState::IDLEMODE};

protected:
    bool is_vsync{false};

public:
    WindowContext(int32_t width, int32_t height, std::string_view const& title)
        : _width(width),
          _height(height),
          _title(title) {}

    [[nodiscard]] inline bool getVsync() const { return is_vsync; }

    inline void initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        _window = glfwCreateWindow(_width, _height, _title.data(), nullptr,
                                   nullptr);
        if (_window == nullptr) {
            spdlog::error("Failed to Create GLFW window!");
            glfwTerminate();
            exit(1);
        }
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwMakeContextCurrent(_window);


        glfwSetWindowUserPointer(_window, this);
        glfwSetKeyCallback(_window, WindowContext::keyCallback);
        glfwSetErrorCallback(errorCallBack);
        glfwSetCharCallback(_window, charCallback);
        glfwSetCharModsCallback(_window, charModsCallback);
        glfwSetMouseButtonCallback(_window, mouseButtonCallback);
        glfwSetCursorPosCallback(_window, cursorPosCallback);
        glfwSetCursorEnterCallback(_window, cursorEnterCallback);
        glfwSetScrollCallback(_window, scrollCallback);
        glfwSetDropCallback(_window, dropCallback);
        glfwSetWindowSizeCallback(_window, windowSizeCallback);
        glfwSetWindowCloseCallback(_window, windowCloseCallback);
    }

    inline void setVsync(bool enable) {
        glfwSwapInterval(enable);
        this->is_vsync = enable;
    }

    [[nodiscard]] inline bool shouldClose() const {
        if (glfwWindowShouldClose(_window)) { return true; }
        glfwPollEvents();
        return false;
    }

    inline void swapBuffers() const { glfwSwapBuffers(_window); }

    inline void destroy() const {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }
};

}// namespace taixu

#endif//TAIXUENGINE_WINDOW_CONTEXT_HPP
