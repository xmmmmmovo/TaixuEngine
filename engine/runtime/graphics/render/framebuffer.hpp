//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_FRAMEBUFFER_HPP
#define TAIXUENGINE_FRAMEBUFFER_HPP

#endif//TAIXUENGINE_FRAMEBUFFER_HPP

namespace taixu {

enum class FrameColorImageFormat {
    NONE = 0,

    RGBA8,
    RED_INTEGER,
};

enum class FrameDepthImageFormat {
    NONE = 0,
    DEPTH24STENCIL8,
};

struct IFrameBufferSpecification {
    FrameColorImageFormat color_image_format = FrameColorImageFormat::NONE;
    FrameDepthImageFormat depth_image_format = FrameDepthImageFormat::NONE;
};

class IFrameBuffer {
    virtual void          bind()             = 0;
    virtual void          unbind()           = 0;
    virtual std::uint32_t getFrameBufferID() = 0;
};


}// namespace taixu