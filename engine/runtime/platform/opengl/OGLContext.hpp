#pragma once
#ifndef TAIXUENGINE_OGLCONTEXT_HPP
#define TAIXUENGINE_OGLCONTEXT_HPP

#include <glad/glad.h>// holds all OpenGL type declarations
#include<memory>
#include"platform/opengl/OGLVertexArray.hpp"
#include"platform/opengl/OGLElementBuffer.hpp"
#include"platform/opengl/OGLVertexBuffer.hpp"
#include"platform/opengl/OGLFrameBuffer.hpp"
#include"glm/glm.hpp"
#include"graphics/render/model.hpp"
#include"graphics/render/camera.hpp"

namespace taixu {

class OGLContext 
{
public:
    glm::vec2 size= {1366, 768};

    std::unique_ptr<OGLVertexArray> vertex_arry;
    //std::vector<OGLVertexBuffer> VBOs;
    //std::unique_ptr<OGLVertexBuffer>  vertex_buffer;
    //std::unique_ptr<OGLElementBuffer> element_buffer;
    std::unique_ptr<OGLFrameBuffer> framebuffer;
    
    void initialize();
    void bindMesh(Mesh mesh);
    void tickbyMesh(Mesh mesh);
    void drawbyElement(Mesh mesh);
    void clear();
};


}
#endif//TAIXUENGINE_OGLCONTEXT_HPP