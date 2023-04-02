#pragma once
#ifndef TAIXUENGINE_OGL_CONTEXT_HPP
#define TAIXUENGINE_OGL_CONTEXT_HPP

#include <glad/glad.h>// holds all OpenGL type declarations

#include <memory>

#include "glm/glm.hpp"
#include "graphics/render/model.hpp"
#include "graphics/render/perspective_camera.hpp"
#include "graphics/render_context.hpp"
#include "platform/opengl/ogl_elementBuffer.hpp"
#include "platform/opengl/ogl_frameBuffer.hpp"
#include "platform/opengl/ogl_vertexArray.hpp"
#include "platform/opengl/ogl_vertexBuffer.hpp"

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