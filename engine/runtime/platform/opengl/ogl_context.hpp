#pragma once
#include "platform/opengl/ogl_frameBuffer.hpp"
#include <memory>
#ifndef TAIXUENGINE_OGL_CONTEXT_HPP
#define TAIXUENGINE_OGL_CONTEXT_HPP

#include "graphics/render_context.hpp"

namespace taixu {

class OGLContext : public IGraphicsContext {
private:
    GLFWwindow                     *_window{nullptr};
    std::unique_ptr<OGLFrameBuffer> _framebuffer{
            std::make_unique<OGLFrameBuffer>(IFrameBufferSpecification{
                    FrameColorImageFormat::RGBA,
                    FrameDepthImageFormat::DEPTH24STENCIL8})};

public:
    void initialize(GLFWwindow *window) override;
    void swapBuffers() override;
    void clear() override;

    IFrameBuffer *getRenderFramebuffer() override;
};

}// namespace taixu
#endif//TAIXUENGINE_OGL_CONTEXT_HPP