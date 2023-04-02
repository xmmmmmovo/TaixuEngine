#include "platform/opengl/ogl_context.hpp"

#include "core/base/macro.hpp"
#include "ogl_context.hpp"

void taixu::OGLContext::initialize(GLFWwindow *window) {
    _window = window;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwMakeContextCurrent(window);
}

void taixu::OGLContext::swapBuffers() { glfwSwapBuffers(_window); }

void taixu::OGLContext::clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
