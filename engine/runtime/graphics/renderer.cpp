//
// Created by xmmmmmovo on 2023/2/14.
//

#include "renderer.hpp"

#include "frag_frag.h"
#include "gui/input_system.hpp"
#include "vert_vert.h"

namespace taixu {
void Renderer::initialize() {
    loadAPI(this->api);
    render_context = std::make_shared<RenderContext>();

    render_context->initialize();

    shaderProgram       = new OGLShaderProgram(VERT_VERT, FRAG_FRAG);

    //Bind buffer for each Mesh

    render_context->bindMesh(
            render_context->getSwapContext()->getData()->model->meshes[0]);
}

void Renderer::tick(float delta_time) {
    clock.update();

    glm::mat4 ProjectionMatrix   = _camera->getProjectionMatrix();
    glm::mat4 ViewMatrix         = _camera->getViewMatrix();
    glm::mat4 ModelMatrix        = glm::mat4(1.0);
    glm::mat4 ModelViewMatrix    = ViewMatrix * ModelMatrix;
    glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
    glm::mat4 MVP                = ProjectionMatrix * ViewMatrix * ModelMatrix;
    shaderProgram->use();

    shaderProgram->set_uniform("MVP", MVP);
    shaderProgram->set_uniform("V", ViewMatrix);
    shaderProgram->set_uniform("M", ModelMatrix);
    shaderProgram->set_uniform("MV3x3", ModelView3x3Matrix);

    shaderProgram->set_uniform("LightPosition_worldspace", lightPos);

    render_context->tickbyMesh(
            render_context->getSwapContext()->model->meshes[0]);
}

void Renderer::clear() {}

void Renderer::resize(float width, float height) {
    size.x = width;
    size.y = height;
}

}// namespace taixu