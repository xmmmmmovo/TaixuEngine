//
// Created by xmmmmmovo on 11/14/2023.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_GLFW_EVENT_HANDLER_63EFF453757040438A313C27EF2676D1
#define ENGINE_SRC_RUNTIME_PLATFORM_GLFW_EVENT_HANDLER_63EFF453757040438A313C27EF2676D1

#include <GLFW/glfw3.h>

#include "runtime/gameplay/gui/event_handler.hpp"

namespace taixu {

class GLFWEventHandler : public EventHandler {
public:
    void handleEvents() override { glfwPollEvents(); GLFW_PRESS }
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_GLFW_EVENT_HANDLER_63EFF453757040438A313C27EF2676D1
