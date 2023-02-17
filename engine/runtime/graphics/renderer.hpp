//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_RENDERER_HPP
#define TAIXUENGINE_RENDERER_HPP

#include "graphics/render/shader.hpp"
#include <memory>
#include <vector>


namespace taixu::cg {
struct Model {
    std::vector<float> vertices;
};
class Render_Data {

    friend class Renderer;

public:
    explicit Render_Data() = default;
    ~Render_Data(){};
    void initialize() {
        model           = std::make_shared<Model>();
        model->vertices = {
                -0.5f, -0.5f, 0.0f,// left
                0.5f,  -0.5f, 0.0f,// right
                0.0f,  0.5f,  0.0f // top};
        };
    }
    Render_Data *getData() { return this; };

protected:
    std::shared_ptr<Model> model;
};

class Render_Context {

    friend class Renderer;

public:
    explicit Render_Context() = default;
    ~Render_Context(){};
    void initialize() {
        render_data = std::make_shared<Render_Data>();
        render_data->initialize();
    };
    Render_Data *getSwapContext() { return render_data->getData(); };

protected:
    std::shared_ptr<Render_Data> render_data;
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
    unsigned int getRenderResult() { return bufferTexId; };


    std::shared_ptr<Render_Context> render_context;
    cg::ShaderProgram              *shaderProgram;

    unsigned int VBO, VAO;
    unsigned int fbo, bufferTexId, rbo;
    glm::vec2    size = {1366, 768};
};


}// namespace taixu::cg

#endif//TAIXUENGINE_RENDERER_HPP
