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
#include "platform/opengl/ogl_context.hpp"
#include "platform/opengl/ogl_shader.hpp"

namespace taixu {

constexpr float delta_time = 0.03333;

class Render_Data {

    friend class Renderer;
    friend class Render_Context;

public:
    explicit Render_Data() = default;
    ~Render_Data()         = default;
    ;
    void initialize() {
        model = std::make_shared<Model_Data>(
                std::string("assets/model/cube.obj"));
    }
    Render_Data*                getData() { return this; };
    std::shared_ptr<Model_Data> model;
};

class Render_Context {

    friend class Renderer;

public:
    explicit Render_Context() = default;
    ~Render_Context()         = default;

    void initialize() {
        render_data = std::make_shared<Render_Data>();
        render_data->initialize();
        ogl_context = std::make_shared<OGLContext>();
        ogl_context->initialize();
    };
    void resize(float width, float height) {
        ogl_context->size.x = width;
        ogl_context->size.y = height;
    };
    void bindMesh(Mesh const& mesh) { ogl_context->bindMesh(mesh); }
    void tickbyMesh(Mesh const& mesh) { ogl_context->tickbyMesh(mesh); };
    Render_Data* getSwapContext() { return render_data->getData(); };

protected:
    std::shared_ptr<Render_Data> render_data;
    std::shared_ptr<OGLContext>  ogl_context;
};

class Renderer {
private:
    RenderAPI api{RenderAPI::OPENGL};
    Clock     clock{};

public:
    void initialize();
    void tick(float delta_time = 0.03333);
    void clear();

    void resize(float width, float height);

    [[nodiscard]] std::uint32_t getRenderResult() const {
        return render_context->ogl_context->framebuffer->getImageid();
    };

    PerspectiveCamera* _camera{nullptr};

    glm::vec3 lightPos = glm::vec3(0, -0.5, -0.5);

    std::shared_ptr<Render_Context> render_context;
    IShaderProgram*                 shaderProgram;

    glm::vec2 size = {1366, 768};
};


}// namespace taixu

#endif//TAIXUENGINE_RENDERER_HPP
