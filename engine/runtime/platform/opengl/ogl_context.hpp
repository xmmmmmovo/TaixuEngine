#pragma once
#ifndef TAIXUENGINE_OGL_CONTEXT_HPP
#define TAIXUENGINE_OGL_CONTEXT_HPP

#include "graphics/render_context.hpp"

namespace taixu {

class OGLContext : public IGraphicsContext {
private:
    GLFWwindow *_window{nullptr};

public:
    void initialize(GLFWwindow *window) override;
    void swapBuffers() override;
    void clear() override;
};

}// namespace taixu
#endif//TAIXUENGINE_OGL_CONTEXT_HPP