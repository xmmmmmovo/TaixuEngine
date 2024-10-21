#include "glfw_window.hpp"

#include "taixu/common/log/logger.hpp"
#include "taixu/gameplay/gui/window.hpp"

namespace taixu {

void GLFWWindow::init() {
    glfwSetErrorCallback(errorCallBack);

    if (GLFW_TRUE != glfwInit()) {
        FATAL_LOG("GLFW init failed!");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void GLFWWindow::showWindow() {
    _window = glfwCreateWindow(_window_info.width, _window_info.height, _window_info.title.data(), nullptr, nullptr);

    if (!_window) {
        glfwTerminate();
        FATAL_LOG("Failed to create GLFW _window");
    }

    glfwSetWindowUserPointer(_window, this);

    glfwSetKeyCallback(_window, keyCallback);
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
    glfwSetWindowContentScaleCallback(_window, windowDPIChangedCallback);

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    float x_scale = 0, y_scale = 0;
    glfwGetWindowContentScale(_window, &x_scale, &y_scale);

    _dpi_scale.x_scale = x_scale;
    _dpi_scale.y_scale = y_scale;
}

void GLFWWindow::destroy() {
    glfwTerminate();
}

void GLFWWindow::handleEvents() {
}

bool GLFWWindow::shouldClose() const {
    return glfwWindowShouldClose(_window);
}

WindowAPI GLFWWindow::getWindowAPI() const {
    return WindowAPI::GLFW;
}

void GLFWWindow::updateTitle(const char* title) {
    glfwSetWindowTitle(_window, title);
}

GLFWwindow* GLFWWindow::getRawWindow() const {
    return _window;
}

bool GLFWWindow::isSupportVulkanImpl() {
    return glfwVulkanSupported() == GLFW_TRUE;
}

VkGlfwExtensions GLFWWindow::getVulkanInstanceExtensions() {
    VkGlfwExtensions ext;
    const char**     ret = glfwGetRequiredInstanceExtensions(&ext.count);
    ext.names.reserve(ext.count);
    std::copy(ret, std::next(ret, ext.count), std::back_inserter(ext.names));
    return ext;
}

void GLFWWindow::errorCallBack(int error, const char* description) {
    ERROR_LOG("GLFW Error: {}, {}", error, description);
}

void GLFWWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onKey(context, key, scancode, action, mods);
}

void GLFWWindow::charCallback(GLFWwindow* window, unsigned int codepoint) {
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onChar(context, codepoint);
}

void GLFWWindow::charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods) {
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onCharMods(context, codepoint, mods);
}

void GLFWWindow::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onMouseButton(context, button, action, mods);
}

void GLFWWindow::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onCursorPos(context, xpos, ypos);
}

void GLFWWindow::cursorEnterCallback(GLFWwindow* window, int entered) {
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onCursorEnter(context, entered);
}

void GLFWWindow::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onScroll(context, xoffset, yoffset);
}

void GLFWWindow::dropCallback(GLFWwindow* window, int count, const char** paths) {
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onDrop(context, count, paths);
}

void GLFWWindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
    DEBUG_LOG("window size changed: {}, {}", width, height);
    auto* context                = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->_window_info.width  = width;
    context->_window_info.height = height;
    context->onReset(context);
    context->onWindowSize(context, width, height);
}

void GLFWWindow::windowDPIChangedCallback(GLFWwindow* window, float xscale, float yscale) {
    DEBUG_LOG("dpi changed: {}, {}", xscale, yscale);
    auto* context               = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->_dpi_scale.x_scale = xscale;
    context->_dpi_scale.y_scale = yscale;
    context->onWindowDPIChanged(context, xscale, yscale);
}

void GLFWWindow::windowCloseCallback(GLFWwindow* window) {
    DEBUG_LOG("clicked close!");
    glfwSetWindowShouldClose(window, true);
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onWindowClose(context);
}

}// namespace taixu
