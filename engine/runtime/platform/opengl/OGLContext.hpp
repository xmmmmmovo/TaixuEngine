#pragma once
#ifndef TAIXUENGINE_OGLCONTEXT_HPP
#define TAIXUENGINE_OGLCONTEXT_HPP


#include"platform/opengl/OGLVertexArray.hpp"
#include"platform/opengl/OGLElementBuffer.hpp"
#include"platform/opengl/OGLVertexBuffer.hpp"
#include"platform/opengl/OGLFrameBuffer.hpp"
#include"glm/glm.hpp"

namespace taixu {

class OGLContext 
{
public:
    glm::vec2 size;

    //std::shared_ptr<OGLVertexArray> vertex_arry;
    //std::shared_ptr<OGLVertexBuffer>  vertex_buffer;
    //std::shared_ptr<OGLElementBuffer> element_buffer;
    //std::shared_ptr<OGLFrameBuffer> framebuffer;

};


}
#endif//TAIXUENGINE_OGLCONTEXT_HPP