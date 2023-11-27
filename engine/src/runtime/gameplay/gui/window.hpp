//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_WINDOW_HPP
#define TAIXUENGINE_WINDOW_HPP

#include <functional>

#include <base/noncopyable.hpp>
#include <management/input/input_state.hpp>
#include <management/input/input_state.hpp>

namespace taixu {

class Window : private Noncopyable {
protected:
    using on_reset_fn        = std::function<void()>;
    using on_key_fn          = std::function<void(int, int, int, int)>;
    using on_char_fn         = std::function<void(unsigned int)>;
    using on_char_mods_fn    = std::function<void(unsigned int, int)>;
    using on_mouse_button_fn = std::function<void(int, int, int)>;
    using on_cursor_pos_fn   = std::function<void(double, double)>;
    using on_cursor_enter_fn = std::function<void(int)>;
    using on_scroll_fn       = std::function<void(double, double)>;
    using on_drop_fn         = std::function<void(int, const char**)>;
    using on_window_size_fn  = std::function<void(int, int)>;
    using on_window_close_fn = std::function<void()>;
    using on_error_fn        = std::function<void(int, char const*)>;

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
    on_error_fn                     on_error;


protected:
    bool _is_vsync{true};
    bool minimize{false};
    bool fullscreen{false};

    InputState const* _input_state{nullptr};

    std::string _title{};
    int32_t     _width{0}, _height{0};

protected:
    void onReset() {
        for (auto const& func : on_reset_fns) { func(); }
    }

    void onKey(int key, int scancode, int action, int mods) {
        for (auto const& func : on_key_fns) {
            func(key, scancode, action, mods);
        }
    }

    void onChar(unsigned int codepoint) {
        for (auto const& func : on_char_fns) { func(codepoint); }
    }

    void onCharMods(unsigned int codepoint, int mods) {
        for (auto const& func : on_char_mods_fns) { func(codepoint, mods); }
    }

    void onMouseButton(int button, int action, int mods) {
        for (auto const& func : on_mouse_button_fns) {
            func(button, action, mods);
        }
    }

    void onCursorPos(double xpos, double ypos) {
        for (auto const& func : on_cursor_pos_fns) { func(xpos, ypos); }
    }

    void onCursorEnter(int entered) {
        for (auto const& func : on_cursor_enter_fns) { func(entered); }
    }

    void onScroll(double xoffset, double yoffset) {
        for (auto const& func : on_scroll_fns) { func(xoffset, yoffset); }
    }

    void onDrop(int count, const char** paths) {
        for (auto const& func : on_drop_fns) { func(count, paths); }
    }

    void onWindowSize(int width, int height) {
        for (auto const& func : on_window_size_fns) { func(width, height); }
    }

    void onWindowClose() {
        for (auto const& func : on_window_close_fns) { func(); }
    }

public:
    virtual void init() = 0;

    virtual void createWindow(std::string_view const& title, int32_t height,
                              int32_t width) = 0;

    virtual void update()  = 0;
    virtual void destroy() = 0;

    // vsync
    [[nodiscard]] bool isVsync() const { return _is_vsync; }
    virtual void       setVsync(bool vsync) = 0;

    virtual void handleEvents() = 0;

    [[nodiscard]] virtual bool shouldClose() const = 0;

    void registerOnResetFn(on_reset_fn const& func) {
        on_reset_fns.push_back(func);
    }

    void registerOnKeyFn(on_key_fn const& func) { on_key_fns.push_back(func); }

    void registerOnCharFn(on_char_fn const& func) {
        on_char_fns.push_back(func);
    }

    void registerOnCharModsFn(on_char_mods_fn const& func) {
        on_char_mods_fns.push_back(func);
    }

    void registerOnMouseButtonFn(on_mouse_button_fn const& func) {
        on_mouse_button_fns.push_back(func);
    }

    void registerOnCursorPosFn(on_cursor_pos_fn const& func) {
        on_cursor_pos_fns.push_back(func);
    }

    void registerOnCursorEnterFn(on_cursor_enter_fn const& func) {
        on_cursor_enter_fns.push_back(func);
    }

    void registerOnScrollFn(on_scroll_fn const& func) {
        on_scroll_fns.push_back(func);
    }

    void registerOnDropFn(on_drop_fn const& func) {
        on_drop_fns.push_back(func);
    }

    void registerOnWindowSizeFn(on_window_size_fn const& func) {
        on_window_size_fns.push_back(func);
    }

    void registerOnWindowCloseFn(on_window_close_fn const& func) {
        on_window_close_fns.push_back(func);
    }

    void setOnError(on_error_fn const&& func) { this->on_error = func; }
};

}// namespace taixu

#endif// TAIXUENGINE_WINDOW_HPP
