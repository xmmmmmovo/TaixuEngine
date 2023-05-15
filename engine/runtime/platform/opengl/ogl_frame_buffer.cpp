#include "ogl_frame_buffer.hpp"

namespace taixu {

GLenum frameColorEnumToOGLType(FrameColorImageFormat const &format) {
    switch (format) {
        case FrameColorImageFormat::RGBA8:
            return GL_RGBA8;
        case FrameColorImageFormat::RGBA:
            return GL_RGBA;
        case FrameColorImageFormat::RED_INTEGER:
            return GL_RED_INTEGER;
        default:
            return GL_NONE;
    }
}

GLenum frameDepthEnumToOGLType(FrameDepthImageFormat const &format) {
    switch (format) {
        case FrameDepthImageFormat::DEPTH24STENCIL8:
            return GL_DEPTH24_STENCIL8;
        default:
            return GL_NONE;
    }
}

void OGLFrameBuffer::createFramebuffer() {
    //Generate a texture image to store rendering results
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glGenTextures(1, &_bufferTexId);
    glBindTexture(GL_TEXTURE_2D, _bufferTexId);

    GLenum const color_format =
            frameColorEnumToOGLType(_specification.color_image_format);
    GLenum const depth_format =
            frameDepthEnumToOGLType(_specification.depth_image_format);

    glTexImage2D(GL_TEXTURE_2D, 0, color_format, _width, _height, 0,
                 color_format, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           _bufferTexId, 0);

    glGenRenderbuffers(1, &_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
    glRenderbufferStorage(
            GL_RENDERBUFFER, depth_format, _width,
            _height);// use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, _rbo);// now actually attach it
    GLenum buffers[4] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(_bufferTexId, buffers);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OGLFrameBuffer::bind() { glBindFramebuffer(GL_FRAMEBUFFER, _fbo); }

void OGLFrameBuffer::unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

std::uint32_t taixu::OGLFrameBuffer::getFBTextureID() { return _bufferTexId; }

void OGLFrameBuffer::resize(int width, int height) {
    this->_width  = width;
    this->_height = height;
    glViewport(0, 0, _width, _height);
    createFramebuffer();
}

}// namespace taixu
