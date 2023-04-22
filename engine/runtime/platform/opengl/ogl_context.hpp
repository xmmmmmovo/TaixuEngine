#pragma once
#ifndef TAIXUENGINE_OGL_CONTEXT_HPP
#define TAIXUENGINE_OGL_CONTEXT_HPP

#include <glad/glad.h>// holds all OpenGL type declarations

#include <memory>

#include "glm/glm.hpp"
#include "graphics/render/model.hpp"
#include "graphics/render/perspective_camera.hpp"
#include "platform/opengl/ogl_elementBuffer.hpp"
#include "platform/opengl/ogl_frameBuffer.hpp"
#include "platform/opengl/ogl_vertexArray.hpp"
#include "platform/opengl/ogl_vertexBuffer.hpp"
#include "platform/opengl/ogl_texture.hpp"

namespace taixu {


class OGLContext {
public:
    glm::vec2 size = {1366, 768};

    std::unique_ptr<OGLVertexArray> vertex_array;
    OGLTexture * texture{nullptr};
    std::uint32_t material_id;
    
    void initialize();
    void bindMesh(Mesh mesh) const;
    //void rebindMesh(Mesh mesh) const;
    void tickMesh(Mesh const& mesh);
    void drawbyElement(Mesh const& mesh);
    void clear();
};


}// namespace taixu
#endif//TAIXUENGINE_OGL_CONTEXT_HPP