//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_RENDERER_HPP
#define TAIXUENGINE_RENDERER_HPP

#include <memory>
#include <vector>

#include "frag_frag.h"
#include "vert_vert.h"
#include "untextured_vert.h"
#include "untextured_frag.h"
#include "core/base/clock.hpp"
#include "graphics/render/model.hpp"
#include "graphics/render/perspective_camera.hpp"
#include "graphics/render/render_api.hpp"
#include "graphics/render/shader.hpp"
#include "graphics/render/texture.hpp"
#include "platform/opengl/ogl_context.hpp"
#include "platform/opengl/ogl_shader.hpp"
#include "platform/opengl/ogl_texture.hpp"
#include "graphics/render/light.hpp"

namespace taixu {
    enum oprationType{ADD,CHANGEMODEL,TRANSFORM};

    struct RenderableModelInfo
    {
        std::uint32_t GO{4294967295}; //Invalid
        const char* file_path{"INVALID"};
        const char* texture_path{"INVALID"};
        std::uint32_t material_id;
        glm::mat4 transform_matrix{glm::mat4(1.0f)};
        oprationType opt;
    };

    struct RenderUint
    {
        std::uint32_t GO{4294967295}; //Invalid
        Model_Data model{};
        std::uint32_t texture_id;
        std::uint32_t material_id;
        std::shared_ptr<OGLContext> GPU;
        bool dirty{false};
        glm::mat4 transform_matrix{glm::mat4(1.0f)};
    };

    struct LightInfo
    {
        //std::uint32_t light_id;
        glm::vec4 light_position{};
        glm::vec4 light_color{};
        
    };

    struct MaterialInfo
    {
        float shininess;
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 emissive;
    };
    

class RenderData {

    friend class Renderer;

    friend class RenderContext;

public:
    explicit RenderData() = default;
    ~RenderData()         = default;
    ;
    void tick() {
        //RenderableModelInfo cube;
        //RenderableModelInfo sphere;
        // cube.file_path = "assets/model/cube.obj";
        // cube.GO = 0;
        // cube.transform_matrix = glm::translate(cube.transform_matrix,glm::vec3(1.0f,1.0f,1.0f));
        // cube.opt = oprationType::ADD;
        // dirty_models.push_back(cube);

        // sphere.file_path = "assets/model/sphere.obj";
        // sphere.GO = 1;
        // sphere.transform_matrix = glm::translate(sphere.transform_matrix,glm::vec3(0.0f,0.0f,0.0f));
        // sphere.opt = oprationType::ADD;
        // dirty_models.push_back(sphere);
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

                    if(modinfo.texture_path != "INVALID")
                    {
                        std::string tempview (modinfo.texture_path);
                        auto texture = std::make_unique<OGLTexture>(tempview,GL_LINEAR,GL_REPEAT);
                        render_uint->texture_id = texture->getTextureID();
                        prepared_textures.push_back(std::move(texture));
                        render_uint->GPU->texture = prepared_textures.back().get();
                    }

                    render_uint->material_id = modinfo.material_id;
                    
                    prepared_models.push_back(render_uint);
                }
                else if(modinfo.opt == oprationType::CHANGEMODEL){}
                else if(modinfo.opt == oprationType::TRANSFORM)
                {
                    for(auto pm:prepared_models)
                    {
                        if(modinfo.GO == pm->GO)
                            pm->transform_matrix = modinfo.transform_matrix;
                    }
                }
            }
            dirty_models.clear();
        }
        
        if(lightisdirty == true)
        {
            prepared_light.clear();
            for(auto& light : light_source)
            {
                LightInfo li;
                li.light_color = light.get()->light_color;
                li.light_position = glm::vec4(light.get()->transform->position,1.0f);
                prepared_light.push_back(li);
            }
            lightisdirty = false;
        }


    }

    void clear(){dirty_models.clear();};
    RenderData*                 getData() { return this; };

    std::vector<RenderableModelInfo> dirty_models;

    std::vector<std::shared_ptr<RenderUint>> prepared_models;

    bool lightisdirty = false;
    std::vector<std::unique_ptr<LightSourse>> light_source;

    std::vector<LightInfo> prepared_light;
    
    std::vector<std::unique_ptr<OGLTexture>> prepared_textures;

    std::vector<MaterialInfo> prepared_materials;
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
        untexturedShaderProgram = new OGLShaderProgram(UNTEXTURED_VERT, UNTEXTURED_FRAG);

        MaterialInfo m1;
        m1.shininess = 96.078443;
        m1.ambient = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        m1.diffuse = glm::vec4(0.64f,0.64f,0.64f,1.0f);
        m1.specular = glm::vec4(0.5f,0.5f,0.5f,1.0f);
        m1.emissive = glm::vec4(0.f,0.f,0.f,1.0f);

        MaterialInfo m2;
        m2.shininess = 100;
        m2.ambient = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        m2.diffuse = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        m2.specular = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        m2.emissive = glm::vec4(0.f,0.f,0.f,1.0f);
        getSwapContext()->prepared_materials.push_back(m1);
        getSwapContext()->prepared_materials.push_back(m2);
    };

    void resize(float width, float height) {
        framesize.x = width;
        framesize.y = height;
    };
  
    void        tickbyMesh() {
        for(auto pm : render_data->prepared_models)
        {
            Transform = pm->transform_matrix;
            material = getSwapContext()->prepared_materials[pm->material_id];

            if(pm->GPU->texture != nullptr)
            {
                bindShader(shaderProgram);

                pm->GPU->texture->bind(0);
            }
            else
            {
                bindShader(untexturedShaderProgram);
            }
            

            pm->GPU->tickMesh(pm->model.meshes[0]);
        }
        //sphere_context = render_data->prepared_models[0]->GPU;
    }

    void        bindShader(OGLShaderProgram* shader){
    glm::mat4 ProjectionMatrix   = _camera->getProjectionMatrix();
    glm::mat4 ViewMatrix         = _camera->getViewMatrix();
    glm::mat4 ModelMatrix        = Transform;
    glm::mat4 ModelViewMatrix    = ViewMatrix * ModelMatrix;
    glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
    glm::mat4 MVP                = ProjectionMatrix * ViewMatrix * ModelMatrix;
    //glm::mat4 Transform          = glm::mat4(1.0f);
    //Transform                    = glm::translate(Transform,glm::vec3(1.0f,1.0f,1.0f));
    shader->use();
    shader->set_uniform("MVP", MVP);
    shader->set_uniform("V", ViewMatrix);
    shader->set_uniform("M", ModelMatrix);
    shader->set_uniform("MV3x3", ModelView3x3Matrix);
    shader->set_uniform("Lights", getSwapContext()->prepared_light);
    shader->set_uniform("shininess", material.shininess);
    shader->set_uniform("ambient", material.ambient);
    shader->set_uniform("diffuse", material.diffuse);
    shader->set_uniform("specular", material.specular);
    shader->set_uniform("emissive", material.emissive);
    shader->set_uniform("cameraPos", _camera->Position);
    shader->set_uniform("texturesampler",0);
    //shaderProgram->set_uniform("LightPosition_worldspace", lightPos);
    //shaderProgram->set_uniform("Light", getSwapContext()->prepared_light);

    }

    RenderData *getSwapContext() { return render_data->getData(); };
    std::unique_ptr<OGLFrameBuffer> framebuffer;
    glm::vec2 framesize{1366,768};
    OGLShaderProgram*                 shaderProgram;
    OGLShaderProgram*                 untexturedShaderProgram;
    PerspectiveCamera* _camera{nullptr};
    glm::vec3 lightPos = glm::vec3(0, 0.5, 0.5);
    glm::mat4 Transform{glm::mat4(1.0f)};
    MaterialInfo material;
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
