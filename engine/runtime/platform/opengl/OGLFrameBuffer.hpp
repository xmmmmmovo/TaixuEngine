
#ifndef TAIXUENGINE_OGLFRAMEBUFFER_HPP
#define TAIXUENGINE_OGLFRAMEBUFFER_HPP

#include"graphics/render/framebuffer.hpp"
#include"graphics/renderer.hpp"
#include"OGLContext.hpp"

namespace taixu {
class OGLFrameBuffer : public IFrameBuffer {
public:
    unsigned int fbo,rbo,bufferTexId;

	void allocate(glm::vec2 frame_size);

	void bind();
	void unbind();
	void getRenderResult();
    unsigned int getImageid();

};


}

#endif//TAIXUENGINE_OGLFRAMEBUFFER_HPP