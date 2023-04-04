//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_RENDERER_HPP
#define TAIXUENGINE_RENDERER_HPP

#include <memory>
#include <vector>

#include "core/base/clock.hpp"
#include "graphics/render/model.hpp"
#include "graphics/render/perspective_camera.hpp"
#include "graphics/render/render_api.hpp"
#include "graphics/render/shader.hpp"
#include "graphics/render/texture.hpp"
#include "graphics/render_context.hpp"
#include "platform/opengl/ogl_context.hpp"
#include "platform/opengl/ogl_shader.hpp"

namespace taixu {

template<typename Context = IGraphicsContext>
class BaseRenderer {
private:
    RenderAPI api{RenderAPI::OPENGL};
    Clock     clock{};

public:
    void initialize();
    void pretick();
    void tick(float delta_time = 0.03333);
    void clear();

    void resize(float width, float height);

    [[nodiscard]] std::uint32_t getRenderResult() const { return 0; };

    PerspectiveCamera *_camera{nullptr};

    glm::vec3 lightPos = glm::vec3(0, -0.5, -0.5);

    std::unique_ptr<Context> render_context{};
    IShaderProgram          *shaderProgram{};

    glm::vec2 size = {1366, 768};
};


}// namespace taixu

#endif//TAIXUENGINE_RENDERER_HPP
