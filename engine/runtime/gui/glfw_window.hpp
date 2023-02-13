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

namespace taixu::gui {

class TX_GLFWwindow : public IWindow {
protected:
    GLFWwindow *window{nullptr};
    bool        initialized{false};
    bool        isVsync{false};

private:
    static void errorCallBack(int error, const char *description);

public:
    TX_GLFWwindow() = default;
    TX_GLFWwindow(IWindowContext const &context_) { context = context_; }
    ~TX_GLFWwindow() override = default;

    void init() override;
    void update() override;
    void destroy() override;

    bool getIsVsync() const;
    void setIsVsync(bool isVsync);
};

}// namespace taixu::gui

#endif//TAIXUENGINE_GLFW_WINDOW_HPP
