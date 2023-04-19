//
// Created by xmmmmmovo on 2023/4/6.
//

#ifndef TAIXUENGINE_OGL_RENDERER_HPP
#define TAIXUENGINE_OGL_RENDERER_HPP

#include "graphics/renderer.hpp"
#include "ogl_context.hpp"

namespace taixu {

class OGLRenderer : public BaseRenderer<OGLContext> {
public:
    void initialize() override;

    void tick(float delta_time) override;
    
    void clear() override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_RENDERER_HPP
