//
// Created by xmmmmmovo on 2023/4/6.
//

#ifndef TAIXUENGINE_OGL_RENDERER_HPP
#define TAIXUENGINE_OGL_RENDERER_HPP

#include <runtime/management/graphics/frontend/cube_renderable.hpp>
#include <runtime/management/graphics/renderer.hpp>
#include "ogl_frame_buffer.hpp"
#include "ogl_shader.hpp"
#include "ogl_texture2d.hpp"
#include "ogl_uniform_buffer.hpp"

#include <memory>

namespace taixu {

class OGLRenderer : public BaseRenderer {
private:
    std::unique_ptr<OGLFrameBuffer> _framebuffer{nullptr};

    OGLUniformBuffer _matrices_ubo{};
    OGLUniformBuffer _lights_ubo{};
    OGLUniformBuffer _material_ubo{};

    CubeRenderable *_cube_renderable{nullptr};

public:
    OGLRenderer() = default;

    void init() override;

    void update(float delta_time) override;
    void clear(const std::array<float, 3> &color) override;

    void clearSurface() override;

    //void addTextures(std::unique_ptr<OGLTexture2D> texture);
    IFrameBuffer *getRenderFramebuffer() override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_RENDERER_HPP
