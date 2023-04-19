#include "ogl_context.hpp"
#include "core/base/macro.hpp"
#include "graphics/render/render_api.hpp"

namespace taixu {

constexpr std::array<float, 3> const CLEAR_COLOR{0.5294117647f, 0.8078431373f,
                                                 0.9215686275f};

void OGLContext::initialize(GLFWwindow *window) {
    _window = window;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwMakeContextCurrent(window);

    // TODO: 检测是否正确
    loadAPI(RenderAPI::OPENGL);
}

void OGLContext::swapBuffers() { glfwSwapBuffers(_window); }

void OGLContext::clear() {
    glClearColor(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}// namespace taixu