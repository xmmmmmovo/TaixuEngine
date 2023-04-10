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

    enum oprationType{ADD,MODEL,TRANSFORM};

    struct RenderableModelInfo
    {
        std::uint32_t GO{4294967295}; //Invalid
        char* file_path{"INVALID"};
        glm::mat4 transform_matrix{glm::mat4(1.0f)};
        oprationType opt;
    };

    struct RenderUint
    {
        std::uint32_t GO{4294967295}; //Invalid
        Model_Data model{};
        std::shared_ptr<OGLContext> GPU;
        bool dirty{false};
        glm::mat4 transform_matrix{glm::mat4(1.0f)};
    };

public:
    explicit RenderData() = default;
    ~RenderData()         = default;
    ;
    void tick() {
        RenderableModelInfo cube;
        RenderableModelInfo sphere;
        cube.file_path = "assets/model/cube.obj";
        cube.GO = 0;
        cube.transform_matrix = glm::translate(cube.transform_matrix,glm::vec3(1.0f,1.0f,1.0f));
        cube.opt = oprationType::ADD;
        dirty_models.push_back(cube);

        sphere.file_path = "assets/model/sphere.obj";
        sphere.GO = 1;
        sphere.transform_matrix = glm::translate(sphere.transform_matrix,glm::vec3(0.0f,0.0f,0.0f));
        sphere.opt = oprationType::ADD;
        dirty_models.push_back(sphere);
        if(dirty_models.size()>0)
        {
            for(auto modinfo : dirty_models)
            {
                if(modinfo.opt == oprationType::ADD)
                {
                    auto render_uint = std::make_shared<RenderUint>();
                    render_uint->GO = modinfo.GO;
                    render_uint->model.loadModel(modinfo.file_path);
                    render_uint->transform_matrix = modinfo.transform_matrix;
                    render_uint->GPU = std::make_shared<OGLContext>();
                    render_uint->GPU->initialize();
                    render_uint->GPU->bindMesh(render_uint->model.meshes[0]);
                    prepared_models.push_back(render_uint);
                }
                else if(modinfo.opt == oprationType::MODEL){}
                else if(modinfo.opt == oprationType::TRANSFORM){}
            }
            dirty_models.clear();
        }
        

    }

    void clear(){dirty_models.clear();};
    RenderData*                 getData() { return this; };

    std::vector<RenderableModelInfo> dirty_models;

    std::vector<std::shared_ptr<RenderUint>> prepared_models;

};

class RenderContext {

    friend class Renderer;

public:
    explicit RenderContext() = default;
    ~RenderContext()         = default;

    void initialize() {
        render_data = std::make_shared<RenderData>();
        
        framebuffer=std::make_unique<OGLFrameBuffer>();
        framebuffer->allocate(framesize);
        
        shaderProgram       = new OGLShaderProgram(VERT_VERT, FRAG_FRAG);
        
        sphere_context = std::make_shared<OGLContext>();

        sphere_context->initialize();
    };

    void resize(float width, float height) {
        framesize.x = width;
        framesize.y = height;
    };
  
    void        tickbyMesh() {
        for(auto pm : render_data->prepared_models)
        {
            Transform = pm->transform_matrix;
            bindShader();
            pm->GPU->tickMesh(pm->model.meshes[0]);
            //int a=0;
        }
        //sphere_context = render_data->prepared_models[0]->GPU;
    }

    void        bindShader(){
    glm::mat4 ProjectionMatrix   = _camera->getProjectionMatrix();
    glm::mat4 ViewMatrix         = _camera->getViewMatrix();
    glm::mat4 ModelMatrix        = Transform;
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

    }

    RenderData *getSwapContext() { return render_data->getData(); };
    std::unique_ptr<OGLFrameBuffer> framebuffer;
    glm::vec2 framesize{1366,768};
    IShaderProgram*                 shaderProgram;
    PerspectiveCamera* _camera{nullptr};
    glm::vec3 lightPos = glm::vec3(0, -0.5, -0.5);
    glm::mat4 Transform{glm::mat4(1.0f)};

    std::vector<std::shared_ptr<OGLContext>> render_meshes;
    std::shared_ptr<OGLContext>  sphere_context;

protected:
    std::shared_ptr<RenderData> render_data;
    
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
        return render_context->framebuffer->getFrameBufferID();
    };

    std::shared_ptr<RenderContext> render_context;
    
    glm::vec2 size = {1366, 768};
};


}// namespace taixu

#endif//TAIXUENGINE_RENDERER_HPP
