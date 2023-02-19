//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_RENDERER_HPP
#define TAIXUENGINE_RENDERER_HPP

#include <memory>
#include <vector>

#include "graphics/camera.hpp"
#include "graphics/render/model.h"
#include "graphics/render/shader.hpp"


namespace taixu::cg {

class Render_Data {

    friend class Renderer;
    friend class Render_Context;

public:
    explicit Render_Data() = default;
    ~Render_Data(){};
    void initialize() {
        model = std::make_shared<Model>(
                std::string("assets/model/cube_flat.obj"));
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
    void bindBuffer(unsigned int  vertex_arry_object,
                    unsigned int &element_buffer_id,
                    unsigned int &vertex_buffer_id, Mesh mesh) {
        glBindVertexArray(vertex_arry_object);
        glGenBuffers(1, &vertex_buffer_id);
        glGenBuffers(1, &element_buffer_id);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        //Bind vertices data of mesh
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex),
                     &mesh.vertices[0], GL_DYNAMIC_DRAW);
        //Bind indices data of mesh
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     mesh.indices.size() * sizeof(unsigned int),
                     &mesh.indices[0], GL_DYNAMIC_DRAW);
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) 0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, TexCoords));
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, Tangent));
        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, Bitangent));
        // ids
        glEnableVertexAttribArray(5);
        glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex),
                               (void *) offsetof(Vertex, m_BoneIDs));
        // weights
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, m_Weights));
        glBindVertexArray(0);
    }
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

    std::shared_ptr<Camera> first_person_camera;

    glm::vec3 lightPos = glm::vec3(0, -0.5, -0.5);

    std::shared_ptr<Render_Context> render_context;
    cg::ShaderProgram              *shaderProgram;

    unsigned int VBO, EBO, VAO;
    unsigned int fbo, bufferTexId, rbo;
    glm::vec2    size = {1366, 768};
};


}// namespace taixu::cg

#endif//TAIXUENGINE_RENDERER_HPP
