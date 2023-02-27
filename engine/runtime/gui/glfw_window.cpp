//
// Created by xmmmmmovo on 2023/2/13.
//

#include "glfw_window.hpp"

#include "gui/event/applicationEvent.h"
#include "gui/event/event.h"
#include "gui/event/keyEvent.h"
#include "gui/event/mouseEvent.h"
#include "core/base/macro.hpp"
namespace taixu {

void TX_GLFWwindow::init() {
    if (window != nullptr) { return; }
    if (!initialized) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        initialized = true;
    }

    window = glfwCreateWindow(context.width, context.height,
                              context.title.data(), nullptr, nullptr);
    if (window == nullptr) {
        spdlog::error("Failed to Create GLFW window!");
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        errorCallBack(-1, "Failed to initialize GLAD");
        exit(1);
    }
    glfwSetWindowUserPointer(window, &context);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    //Set GLFW callbacks
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode,
                                    int action, int mods) {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                event::KeyPressEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                event::KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                event::KeyPressEvent event(key, true);
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

        event::KeyTypedEvent event(1);
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button,
                                            int action, int mods) {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                event::MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                event::MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset,
                                       double yOffset) {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

        event::MouseScrolledEvent event((float) xOffset, (float) yOffset);
        data.EventCallback(event);
    });
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos,
                                          double yPos) {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

        event::MouseMovedEvent event((float) xPos, (float) yPos);
        data.EventCallback(event);
    });
}

void TX_GLFWwindow::update() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void TX_GLFWwindow::destroy() { glfwDestroyWindow(window); }

void TX_GLFWwindow::errorCallBack(int error, const char* description) {
    spdlog::error("GLFW Error: {}", description);
}

bool TX_GLFWwindow::getIsVsync() const { return isVsync; }

void TX_GLFWwindow::setIsVsync(bool enable) {
    if (enable) {
        // turn off if you are using complex shader
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }

    isVsync = enable;
}

}// namespace taixu
