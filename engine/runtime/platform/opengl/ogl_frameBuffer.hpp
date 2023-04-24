
#ifndef TAIXUENGINE_OGL_FRAMEBUFFER_HPP
#define TAIXUENGINE_OGL_FRAMEBUFFER_HPP

#include <glad/glad.h>// holds all OpenGL type declarations

#include <glm/glm.hpp>

#include "graphics/render/framebuffer.hpp"

namespace taixu {
class OGLFrameBuffer : public IFrameBuffer {
private:
    int    _width{0}, _height{0};
    GLuint _fbo{}, _rbo{}, _bufferTexId{};

    IFrameBufferSpecification _specification{};

    bool created{false};

    void createFramebuffer();

public:
    explicit OGLFrameBuffer(const IFrameBufferSpecification &specification)
        : _specification(specification) {}

    void          bind() override;
    void          unbind() override;
    std::uint32_t getFBTextureID() override;
    void          resize(int width, int height) override;
};


}// namespace taixu

#endif//TAIXUENGINE_OGL_FRAMEBUFFER_HPP