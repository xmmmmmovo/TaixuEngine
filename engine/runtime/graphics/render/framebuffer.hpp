//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_FRAMEBUFFER_HPP
#define TAIXUENGINE_FRAMEBUFFER_HPP

#endif//TAIXUENGINE_FRAMEBUFFER_HPP

namespace taixu {
class IFrameBuffer {
    virtual void bind()            = 0;
    virtual void unbind()          = 0;
    virtual void getRenderResult() = 0;
};


}// namespace taixu