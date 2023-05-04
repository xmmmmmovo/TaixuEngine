//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_WINDOW_CONTEXT_HPP
#define TAIXUENGINE_WINDOW_CONTEXT_HPP


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <string>

#include "core/base/macro.hpp"
#include "gameplay/player/perspective_camera.hpp"
#include "management/graphics/render/render_api.hpp"

namespace taixu {
/**
 * @brief 仅在父类使用为Prop 在所有类中使用为Context
 */
class WindowContext {
protected:
    using on_reset_fn        = std::function<void()>;
    using on_key_fn          = std::function<void(int, int, int, int)>;
    using on_char_fn         = std::function<void(unsigned int)>;
    using on_char_mods_fn    = std::function<void(unsigned int, int)>;
    using on_mouse_button_fn = std::function<void(int, int, int)>;
    using on_cursor_pos_fn   = std::function<void(double, double)>;
    using on_cursor_enter_fn = std::function<void(int)>;
    using on_scroll_fn       = std::function<void(double, double)>;
    using on_drop_fn         = std::function<void(int, const char **)>;
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

    static void errorCallBack(int error, const char *description) {
        spdlog::error("GLFW Error: {}, {}", error, description);
    }

    static void keyCallback(GLFWwindow *window, int key, int scancode,
                            int action, int mods) {
        auto *context =
                static_cast<WindowContext *>(glfwGetWindowUserPointer(window));
        context->onKey(key, scancode, action, mods);
    }

    static void charCallback(GLFWwindow *window, unsigned int codepoint) {
        auto *context =
                static_cast<WindowContext *>(glfwGetWindowUserPointer(window));
        context->onChar(codepoint);
    }

    static void charModsCallback(GLFWwindow *window, unsigned int codepoint,
                                 int mods) {
        auto *context =
                static_cast<WindowContext *>(glfwGetWindowUserPointer(window));
        context->onCharMods(codepoint, mods);
    }

    static void mouseButtonCallback(GLFWwindow *window, int button, int action,
                                    int mods) {
        auto *context =
                static_cast<WindowContext *>(glfwGetWindowUserPointer(window));
        context->onMouseButton(button, action, mods);
    }

    static void cursorPosCallback(GLFWwindow *window, double xpos,
                                  double ypos) {
        auto *context =
                static_cast<WindowContext *>(glfwGetWindowUserPointer(window));
        context->onCursorPos(xpos, ypos);
    }

    static void cursorEnterCallback(GLFWwindow *window, int entered) {
        auto *context =
                static_cast<WindowContext *>(glfwGetWindowUserPointer(window));
        context->onCursorEnter(entered);
    }

    static void scrollCallback(GLFWwindow *window, double xoffset,
                               double yoffset) {
        auto *context =
                static_cast<WindowContext *>(glfwGetWindowUserPointer(window));
        context->onScroll(xoffset, yoffset);
    }

    static void dropCallback(GLFWwindow *window, int count,
                             const char **paths) {
        auto *context =
                static_cast<WindowContext *>(glfwGetWindowUserPointer(window));
        context->onDrop(count, paths);
    }

    static void windowSizeCallback(GLFWwindow *window, int width, int height) {
        auto *context =
                static_cast<WindowContext *>(glfwGetWindowUserPointer(window));
        context->_width  = width;
        context->_height = height;
        context->onReset();
        context->onWindowSize(width, height);
    }

    static void windowCloseCallback(GLFWwindow *window) {
        glfwSetWindowShouldClose(window, true);
        auto *context =
                static_cast<WindowContext *>(glfwGetWindowUserPointer(window));
        context->onWindowClose();
    }

    void onReset() {
        for (auto const &func : on_reset_fns) { func(); }
    }

    void onKey(int key, int scancode, int action, int mods) {
        for (auto const &func : on_key_fns) {
            func(key, scancode, action, mods);
        }
    }

    void onChar(unsigned int codepoint) {
        for (auto const &func : on_char_fns) { func(codepoint); }
    }

    void onCharMods(unsigned int codepoint, int mods) {
        for (auto const &func : on_char_mods_fns) { func(codepoint, mods); }
    }

    void onMouseButton(int button, int action, int mods) {
        for (auto const &func : on_mouse_button_fns) {
            func(button, action, mods);
        }
    }

    void onCursorPos(double xpos, double ypos) {
        for (auto const &func : on_cursor_pos_fns) { func(xpos, ypos); }
    }

    void onCursorEnter(int entered) {
        for (auto const &func : on_cursor_enter_fns) { func(entered); }
    }

    void onScroll(double xoffset, double yoffset) {
        for (auto const &func : on_scroll_fns) { func(xoffset, yoffset); }
    }

    void onDrop(int count, const char **paths) {
        for (auto const &func : on_drop_fns) { func(count, paths); }
    }

    void onWindowSize(int width, int height) {
        for (auto const &func : on_window_size_fns) { func(width, height); }
    }

    void onWindowClose() {
        for (auto const &func : on_window_close_fns) { func(); }
    }

public:
    void registerOnResetFn(on_reset_fn const &func) {
        on_reset_fns.push_back(func);
    }

    void registerOnKeyFn(on_key_fn const &func) { on_key_fns.push_back(func); }

    void registerOnCharFn(on_char_fn const &func) {
        on_char_fns.push_back(func);
    }

    void registerOnCharModsFn(on_char_mods_fn const &func) {
        on_char_mods_fns.push_back(func);
    }

    void registerOnMouseButtonFn(on_mouse_button_fn const &func) {
        on_mouse_button_fns.push_back(func);
    }

    void registerOnCursorPosFn(on_cursor_pos_fn const &func) {
        on_cursor_pos_fns.push_back(func);
    }

    void registerOnCursorEnterFn(on_cursor_enter_fn const &func) {
        on_cursor_enter_fns.push_back(func);
    }

    void registerOnScrollFn(on_scroll_fn const &func) {
        on_scroll_fns.push_back(func);
    }

    void registerOnDropFn(on_drop_fn const &func) {
        on_drop_fns.push_back(func);
    }

    void registerOnWindowSizeFn(on_window_size_fn const &func) {
        on_window_size_fns.push_back(func);
    }

    void registerOnWindowCloseFn(on_window_close_fn const &func) {
        on_window_close_fns.push_back(func);
    }

public:
    GLFWwindow *_window{nullptr};

    std::int32_t _width{0};
    std::int32_t _height{0};

    std::string_view _title{};

    /**
     * @brief editor state
     */
    EngineState _state{EngineState::EDITORMODE};

protected:
    bool                                       is_vsync{false};
    std::unique_ptr<AbstractGraphicsAPILoader> _api_loader;

    inline void
    initWindow(std::unique_ptr<AbstractGraphicsAPILoader> api_loader,
               bool                                       vsync = false) {
        if (!glfwInit()) {
            spdlog::error("Failed to init GLFW!");
            exit(1);
        }

        api_loader->initLoad();

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        _window = glfwCreateWindow(_width, _height, _title.data(), nullptr,
                                   nullptr);
        if (_window == nullptr) {
            spdlog::error("Failed to Create GLFW window!");
            glfwTerminate();
            exit(1);
        }

        api_loader->apiLoad(_window);

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

        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        _api_loader = std::move(api_loader);
        setVsync(vsync);
    }

public:
    explicit WindowContext(
            int32_t width, int32_t height, std::string_view const &title,
            std::unique_ptr<AbstractGraphicsAPILoader> api_loader,
            bool                                       vsync = false)
        : _width(width), _height(height), _title(title) {
        initWindow(std::move(api_loader), vsync);
    }

    [[nodiscard]] inline bool getVsync() const { return is_vsync; }

    inline void setVsync(bool enable) {
        glfwSwapInterval(enable);
        this->is_vsync = enable;
    }

    [[nodiscard]] inline bool shouldClose() const {
        if (glfwWindowShouldClose(_window)) { return true; }
        glfwPollEvents();
        return false;
    }

    inline void destroy() const {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    inline void swapBuffers() const { _api_loader->swapBuffers(); }

public:
    ImVec2 _mouse_pos{0.0f, 0.0f};
    ImVec2 _last_mouse_pos{-1.f, -1.f};
    bool   _cam_mode{false};
};

}// namespace taixu

#endif//TAIXUENGINE_WINDOW_CONTEXT_HPP
