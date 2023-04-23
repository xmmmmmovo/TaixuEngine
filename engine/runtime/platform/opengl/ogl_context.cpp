#include "ogl_context.hpp"
#include "core/base/macro.hpp"
#include "graphics/render/render_api.hpp"

namespace taixu {

void OGLContext::initialize(GLFWwindow *window) {
    _window = window;


    this->_framebuffer = std::make_unique<OGLFrameBuffer>(
            IFrameBufferSpecification{FrameColorImageFormat::RGBA,
                                      FrameDepthImageFormat::DEPTH24STENCIL8});
}

void OGLContext::swapBuffers() { glfwSwapBuffers(_window); }

IFrameBuffer *OGLContext::getRenderFramebuffer() { return _framebuffer.get(); }

}// namespace taixu