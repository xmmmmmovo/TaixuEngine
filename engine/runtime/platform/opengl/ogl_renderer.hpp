//
// Created by xmmmmmovo on 2023/4/6.
//

#ifndef TAIXUENGINE_OGL_RENDERER_HPP
#define TAIXUENGINE_OGL_RENDERER_HPP

#include "management/graphics/renderer.hpp"
#include "ogl_frame_buffer.hpp"
#include "ogl_shader.hpp"
#include "ogl_uniform_buffer.hpp"
#include "skybox_frag.h"
#include "skybox_vert.h"

#include <memory>

namespace taixu {

class OGLRenderer : public BaseRenderer {
private:
    std::unique_ptr<OGLFrameBuffer> _framebuffer{nullptr};

    OGLUniformBuffer _matrices_ubo{};
    OGLShaderProgram _skybox_shader{SKYBOX_VERT, SKYBOX_FRAG};

public:
    OGLRenderer() = default;

    void init() override;

    void update() override;
    void clear(const std::array<float, 3> &color) override;

    void clearSurface() override;

    IFrameBuffer *getRenderFramebuffer() override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_RENDERER_HPP
