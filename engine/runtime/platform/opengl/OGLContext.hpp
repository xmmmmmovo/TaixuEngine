#pragma once
#ifndef TAIXUENGINE_OGLCONTEXT_HPP
#define TAIXUENGINE_OGLCONTEXT_HPP

#include <glad/glad.h>// holds all OpenGL type declarations

#include <memory>

#include "glm/glm.hpp"
#include "graphics/render/model.hpp"
#include "graphics/render/perspective_camera.hpp"
#include "platform/opengl/OGLElementBuffer.hpp"
#include "platform/opengl/OGLFrameBuffer.hpp"
#include "platform/opengl/OGLVertexArray.hpp"
#include "platform/opengl/OGLVertexBuffer.hpp"

namespace taixu {

class OGLContext {
public:
    glm::vec2 size = {1366, 768};

    std::unique_ptr<OGLVertexArray> vertex_array;
    //std::vector<OGLVertexBuffer> VBOs;
    //std::unique_ptr<OGLVertexBuffer>  vertex_buffer;
    //std::unique_ptr<OGLElementBuffer> element_buffer;
    std::unique_ptr<OGLFrameBuffer> framebuffer;

    void initialize();
    void bindMesh(Mesh mesh) const;
    //void rebindMesh(Mesh mesh) const;
    void tickbyMesh(Mesh const& mesh);
    void drawbyElement(Mesh const& mesh);
    void clear();
};


}// namespace taixu
#endif//TAIXUENGINE_OGLCONTEXT_HPP