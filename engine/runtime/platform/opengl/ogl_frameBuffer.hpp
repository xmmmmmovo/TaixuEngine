
#ifndef TAIXUENGINE_OGL_FRAMEBUFFER_HPP
#define TAIXUENGINE_OGL_FRAMEBUFFER_HPP

#include"graphics/render/framebuffer.hpp"
#include <glad/glad.h>// holds all OpenGL type declarations
#include <glm/glm.hpp>

namespace taixu {
class OGLFrameBuffer : public IFrameBuffer {
public:
    std::uint32_t fbo,rbo,bufferTexId;

	void allocate(glm::vec2 frame_size);

	void bind()override;
	void unbind()override;
	void          getFrameBufferID()override;
    std::uint32_t getImageid();
};


}

#endif//TAIXUENGINE_OGL_FRAMEBUFFER_HPP