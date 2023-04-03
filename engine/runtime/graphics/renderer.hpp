//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_RENDERER_HPP
#define TAIXUENGINE_RENDERER_HPP

#include <memory>
#include <vector>

#include "frag_frag.h"
#include "vert_vert.h"
#include "core/base/clock.hpp"
#include "graphics/render/model.hpp"
#include "graphics/render/perspective_camera.hpp"
#include "graphics/render/render_api.hpp"
#include "graphics/render/shader.hpp"
#include "graphics/render/texture.hpp"
#include "platform/opengl/ogl_context.hpp"
#include "platform/opengl/ogl_shader.hpp"

namespace taixu {

class RenderData {

    friend class Renderer;

    friend class RenderContext;
public:
    explicit RenderData() = default;
    ~RenderData()         = default;
    ;
    void initialize() {
        sphere = std::make_shared<Model_Data>(
                 std::string("assets/model/cube.obj"));
        model = std::make_shared<Model_Data>(
                 std::string("assets/model/teapot.obj"));

    }
    RenderData*                 getData() { return this; };
    std::shared_ptr<Model_Data> model;
    std::shared_ptr<Model_Data> sphere;
};

class RenderContext {

    friend class Renderer;

public:
    explicit RenderContext() = default;
    ~RenderContext()         = default;

    void initialize() {
        render_data = std::make_shared<RenderData>();
        render_data->initialize();
        framebuffer=std::make_unique<OGLFrameBuffer>();
        framebuffer->allocate(framesize);
        
        shaderProgram       = new OGLShaderProgram(VERT_VERT, FRAG_FRAG);
        
        sphere_context = std::make_shared<OGLContext>();
        sphere_context->initialize();

        teapot_context = std::make_shared<OGLContext>();
        teapot_context->initialize();
    };

    void resize(float width, float height) {
        framesize.x = width;
        framesize.y = height;
    };

    void         bindMesh(Mesh const& mesh,std::string const &mode) { 
        if(mode == "sphere")
            sphere_context->bindMesh(mesh);
        else if(mode == "teapot")
            teapot_context->bindMesh(mesh); 
    }
    
    void        tickbyMesh(Mesh const& mesh,std::string const& mode) { 
        if(mode=="sphere")
        sphere_context->tickbyMesh(mesh);
        else if(mode=="teapot")
        teapot_context->tickbyMesh(mesh);
    };


    void        bindShader(){
    glm::mat4 ProjectionMatrix   = _camera->getProjectionMatrix();
    glm::mat4 ViewMatrix         = _camera->getViewMatrix();
    glm::mat4 ModelMatrix        = glm::mat4(1.0);
    glm::mat4 ModelViewMatrix    = ViewMatrix * ModelMatrix;
    glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
    glm::mat4 MVP                = ProjectionMatrix * ViewMatrix * ModelMatrix;
    //glm::mat4 Transform          = glm::mat4(1.0f);
    //Transform                    = glm::translate(Transform,glm::vec3(1.0f,1.0f,1.0f));

    shaderProgram->use();

    shaderProgram->set_uniform("MVP", MVP);
    shaderProgram->set_uniform("V", ViewMatrix);
    shaderProgram->set_uniform("M", ModelMatrix);
    shaderProgram->set_uniform("MV3x3", ModelView3x3Matrix);
    shaderProgram->set_uniform("LightPosition_worldspace", lightPos);
    shaderProgram->set_uniform("transform", Transform);

    }

    Render_Data *getSwapContext() { return render_data->getData(); };
    std::unique_ptr<OGLFrameBuffer> framebuffer;
    glm::vec2 framesize{1366,768};
    IShaderProgram*                 shaderProgram;
    PerspectiveCamera* _camera{nullptr};
    glm::vec3 lightPos = glm::vec3(0, -0.5, -0.5);
    glm::mat4 Transform{glm::mat4(1.0f)};

    std::shared_ptr<OGLContext>  sphere_context;
    std::shared_ptr<OGLContext>  teapot_context;

protected:
    std::shared_ptr<Render_Data> render_data;
    
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
        return render_context->framebuffer->getImageid();
    };

    std::shared_ptr<Render_Context> render_context;
    
    glm::vec2 size = {1366, 768};
};


}// namespace taixu

#endif//TAIXUENGINE_RENDERER_HPP
