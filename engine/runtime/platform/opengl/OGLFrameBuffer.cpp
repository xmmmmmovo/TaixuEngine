#include "OGLFrameBuffer.hpp"

void taixu::OGLFrameBuffer::allocate(glm::vec2 frame_size) {
    //Generate a texture image to store rendering results
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glGenTextures(1, &bufferTexId);
    glBindTexture(GL_TEXTURE_2D, bufferTexId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_size.x, frame_size.y, 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           bufferTexId, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(
            GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 
            frame_size.x,
            frame_size.y);// use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, rbo);// now actually attach it
    GLenum buffers[4] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(bufferTexId, buffers);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void taixu::OGLFrameBuffer::bind() 
{ 
    glBindFramebuffer(GL_FRAMEBUFFER, bufferTexId);
}

void taixu::OGLFrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void taixu::OGLFrameBuffer::getRenderResult() { getImageid(); }

std::uint32_t taixu::OGLFrameBuffer::getImageid() { return bufferTexId; }
