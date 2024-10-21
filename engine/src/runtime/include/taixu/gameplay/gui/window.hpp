//
// Created by xmmmmmovo on 2023/2/12.
//

#pragma once

#include <functional>

#include "taixu/common/base/core.hpp"
#include "taixu/common/base/macro.hpp"
#include "taixu/common/designs/noncopyable.hpp"

TX_NAMESPACE_BEGIN

struct WindowInfo {
    std::string_view title{};
    int32_t          width{0};
    int32_t          height{0};
};

struct DPIScale {
    float x_scale{0.0f};
    float y_scale{0.0f};
};

struct WindowState {
    bool minimize{false};
    bool fullscreen{false};
};

class GLFWWindow;

/**
 * @brief Window base class, for processing events and window utils
 */
class Window : public Noncopyable {
    friend class GLFWWindow;

private:
    using on_reset_fn              = std::function<void(Window*)>;
    using on_key_fn                = std::function<void(Window*, int, int, int, int)>;
    using on_char_fn               = std::function<void(Window*, unsigned int)>;
    using on_char_mods_fn          = std::function<void(Window*, unsigned int, int)>;
    using on_mouse_button_fn       = std::function<void(Window*, int, int, int)>;
    using on_cursor_pos_fn         = std::function<void(Window*, double, double)>;
    using on_cursor_enter_fn       = std::function<void(Window*, int)>;
    using on_scroll_fn             = std::function<void(Window*, double, double)>;
    using on_drop_fn               = std::function<void(Window*, int, const char**)>;
    using on_window_size_fn        = std::function<void(Window*, int, int)>;
    using on_window_dpi_changed_fn = std::function<void(Window*, float, float)>;
    using on_window_close_fn       = std::function<void(Window*)>;
    using on_error_fn              = std::function<void(Window*, int, char const*)>;

    std::vector<on_reset_fn>              _on_reset_fns{};
    std::vector<on_key_fn>                _on_key_fns{};
    std::vector<on_char_fn>               _on_char_fns{};
    std::vector<on_char_mods_fn>          _on_char_mods_fns{};
    std::vector<on_mouse_button_fn>       _on_mouse_button_fns{};
    std::vector<on_cursor_pos_fn>         _on_cursor_pos_fns{};
    std::vector<on_cursor_enter_fn>       _on_cursor_enter_fns{};
    std::vector<on_scroll_fn>             _on_scroll_fns{};
    std::vector<on_drop_fn>               _on_drop_fns{};
    std::vector<on_window_size_fn>        _on_window_size_fns{};
    std::vector<on_window_dpi_changed_fn> _on_window_dpi_changed_fns{};
    std::vector<on_window_close_fn>       _on_window_close_fns{};
    on_error_fn                           _on_error{};

private:
    PROTOTYPE_ONLY_GETTER_CONST(protected, DPIScale, dpi_scale);
    PROTOTYPE_ONLY_GETTER_CONST(protected, WindowInfo, window_info);
    PROTOTYPE_ONLY_GETTER_CONST(protected, WindowState, window_state);

public:
    explicit Window(WindowInfo const& window_info);

    virtual void                    init()               = 0;
    virtual void                    showWindow()         = 0;
    virtual void                    destroy()            = 0;
    virtual void                    handleEvents()       = 0;
    [[nodiscard]] virtual bool      shouldClose() const  = 0;
    [[nodiscard]] virtual WindowAPI getWindowAPI() const = 0;

    void    update();
    RetCode setTitle(std::string_view title);

protected:
    virtual void updateTitle(const char* title) = 0;

protected:
    // NOLINTBEGIN
    void onReset(Window* window) const {
        for (auto&& func : _on_reset_fns) {
            func(window);
        }
    }

    void onKey(Window* window, const int key, const int scancode, const int action, const int mods) const {
        for (auto&& func : _on_key_fns) {
            func(window, key, scancode, action, mods);
        }
    }

    void onChar(Window* window, const unsigned int codepoint) const {
        for (auto&& func : _on_char_fns) {
            func(window, codepoint);
        }
    }

    void onCharMods(Window* window, const unsigned int codepoint, const int mods) const {
        for (auto&& func : _on_char_mods_fns) {
            func(window, codepoint, mods);
        }
    }

    void onMouseButton(Window* window, const int button, const int action, const int mods) const {
        for (auto&& func : _on_mouse_button_fns) {
            func(window, button, action, mods);
        }
    }

    void onCursorPos(Window* window, const double xpos, const double ypos) const {
        for (auto&& func : _on_cursor_pos_fns) {
            func(window, xpos, ypos);
        }
    }

    void onCursorEnter(Window* window, const int entered) const {
        for (auto&& func : _on_cursor_enter_fns) {
            func(window, entered);
        }
    }

    void onScroll(Window* window, const double xoffset, const double yoffset) const {
        for (auto&& func : _on_scroll_fns) {
            func(window, xoffset, yoffset);
        }
    }

    void onDrop(Window* window, const int count, const char** paths) const {
        for (auto&& func : _on_drop_fns) {
            func(window, count, paths);
        }
    }

    void onWindowSize(Window* window, const int width, const int height) const {
        for (auto&& func : _on_window_size_fns) {
            func(window, width, height);
        }
    }

    void onWindowDPIChanged(Window* window, const float xscale, const float yscale) const {
        for (auto&& func : _on_window_dpi_changed_fns) {
            func(window, xscale, yscale);
        }
    }

    void onWindowClose(Window* window) const {
        for (auto&& func : _on_window_close_fns) {
            func(window);
        }
    }

    // NOLINTEND

public:
    void registerOnResetFn(on_reset_fn const& func) {
        _on_reset_fns.push_back(func);
    }

    void registerOnKeyFn(on_key_fn const& func) {
        _on_key_fns.push_back(func);
    }

    void registerOnCharFn(on_char_fn const& func) {
        _on_char_fns.push_back(func);
    }

    void registerOnCharModsFn(on_char_mods_fn const& func) {
        _on_char_mods_fns.push_back(func);
    }

    void registerOnMouseButtonFn(on_mouse_button_fn const& func) {
        _on_mouse_button_fns.push_back(func);
    }

    void registerOnCursorPosFn(on_cursor_pos_fn const& func) {
        _on_cursor_pos_fns.push_back(func);
    }

    void registerOnCursorEnterFn(on_cursor_enter_fn const& func) {
        _on_cursor_enter_fns.push_back(func);
    }

    void registerOnScrollFn(on_scroll_fn const& func) {
        _on_scroll_fns.push_back(func);
    }

    void registerOnDropFn(on_drop_fn const& func) {
        _on_drop_fns.push_back(func);
    }

    void registerOnWindowSizeFn(on_window_size_fn const& func) {
        _on_window_size_fns.push_back(func);
    }

    void registerOnWindowCloseFn(on_window_close_fn const& func) {
        _on_window_close_fns.push_back(func);
    }

    void setOnError(on_error_fn const&& func) {
        this->_on_error = func;
    }
};

TX_NAMESPACE_END
