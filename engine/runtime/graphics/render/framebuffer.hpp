//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_FRAMEBUFFER_HPP
#define TAIXUENGINE_FRAMEBUFFER_HPP

#endif//TAIXUENGINE_FRAMEBUFFER_HPP

namespace taixu {

enum class FrameColorImageFormat {
    None = 0,

    RGBA8,
    RED_INTEGER,
};

enum class FrameDepthImageFormat {
    None = 0,
    DEPTH24STENCIL8,
};

class IFrameBuffer {
    virtual void bind()             = 0;
    virtual void unbind()           = 0;
    virtual void getFrameBufferID() = 0;
};


}// namespace taixu