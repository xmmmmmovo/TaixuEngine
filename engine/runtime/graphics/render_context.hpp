//
// Created by xmmmmmovo on 2023/3/21.
//

#ifndef TAIXUENGINE_RENDER_CONTEXT_HPP
#define TAIXUENGINE_RENDER_CONTEXT_HPP

#include <GLFW/glfw3.h>

namespace taixu {
class IGraphicsContext : private noncopyable {
public:
    virtual void initialize(GLFWwindow *window) = 0;
    virtual void swapBuffers()                  = 0;
    virtual void clear()                        = 0;
};
}// namespace taixu

#endif//TAIXUENGINE_RENDER_CONTEXT_HPP
