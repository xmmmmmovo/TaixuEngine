//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_RENDERER_HPP
#define TAIXUENGINE_RENDERER_HPP

#include <memory>
#include <vector>

#include "graphics/render/model.hpp"
#include "graphics/render/perspective_camera.hpp"
#include "graphics/render/shader.hpp"
#include "graphics/render/texture.hpp"
#include "platform/opengl/OGLContext.hpp"
#include "platform/opengl/OGLShader.hpp"
#include "resource/ecs/entity_component_system.hpp"
#include "resource/ecs/entity_component/mesh/mesh_component.hpp"
namespace taixu {

constexpr float delta_time = 0.03333;

class Render_Data {

    friend class Renderer;
    friend class Render_Context;
    //friend void MeshComponent::loadModelData();
public:
    explicit Render_Data() = default;
    ~Render_Data()= default;;
    void initialize() {
        model = std::make_shared<Model_Data>(
                std::string("assets/model/cube.obj"));
    }
    Render_Data *getData() { return this; };
    //std::vector<Model>
    std::shared_ptr<Model_Data> model;
};

class Render_Context {

    friend class Renderer;

public:
    explicit Render_Context() = default;
    ~Render_Context()= default;;
    void initialize() {
        render_data = std::make_shared<Render_Data>();
        render_data->initialize();
        ogl_context=std::make_shared<OGLContext>();
        ogl_context->initialize();
    };
    void resize(float width, float height)
    {
        ogl_context->size.x=width;
        ogl_context->size.y=height;
    };
    void bindMesh(Mesh mesh) {
        ogl_context->bindMesh(mesh);
    }
    void tickbyMesh(Mesh mesh)
    {
        ogl_context->tickbyMesh(mesh);
    };
    Render_Data *getSwapContext() { return render_data->getData(); };

protected:
    std::shared_ptr<Render_Data> render_data;
    std::shared_ptr<OGLContext> ogl_context;
};

class Renderer {
    //std::shared_ptr<Render_Resource> RenderQueue;
public:
    explicit Renderer() = default;
    ~Renderer(){};
    void initialize();
    void tick(float delta_time = 0.03333);
    void clear();

    void         resize(float width, float height);
    void         processInput(std::string input);
    void         processInput(glm::vec2 mouse_pos);
    bool         first_mouse = true;
    float        last_x, last_y;
    void         processInput(float scroll_yoffset);
    //unsigned int getRenderResult() { return bufferTexId; };
    std::uint32_t getRenderResult() { return render_context->ogl_context->framebuffer->getImageid(); };
    std::shared_ptr<PerspectiveCamera> first_person_camera;
    
    glm::vec3 lightPos = glm::vec3(0, -0.5, -0.5);
    
    std::shared_ptr<Render_Context> render_context;
    IShaderProgram                 *shaderProgram;

    unsigned int VBO, EBO, VAO;
    unsigned int fbo, bufferTexId, rbo;
    glm::vec2    size = {1366, 768};
};


}// namespace taixu

#endif//TAIXUENGINE_RENDERER_HPP
