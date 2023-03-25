//
// Created by xmmmmmovo on 2023/2/14.
//

#include "renderer.hpp"

#include "frag_frag.h"
#include "vert_vert.h"

namespace taixu {
void Renderer::initialize() {
    render_context = std::make_shared<Render_Context>();

    render_context->initialize();

    first_person_camera = std::make_shared<Camera>();
    shaderProgram       = new OGLShaderProgram(VERT_VERT, FRAG_FRAG);

    //Bind buffer for each Mesh

    render_context->bindMesh(render_context->getSwapContext()->getData()->model->meshes[0]);
    
}
void Renderer::tick(float delta_time) {
    glm::mat4 ProjectionMatrix   = first_person_camera->getProjectionMatrix();
    glm::mat4 ViewMatrix         = first_person_camera->getViewMatrix();
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
    
    render_context->tickbyMesh(render_context->getSwapContext()->model->meshes[0]);
}
void Renderer::clear() {}
void Renderer::resize(float width, float height) {
    size.x = width;
    size.y = height;
}
void Renderer::processInput(std::string input) {

    if (input == "FORWARD")
        first_person_camera->ProcessKeyboard(taixu::Camera_Movement::FORWARD,
                                             delta_time);
    if (input == "BACKWARD")
        first_person_camera->ProcessKeyboard(taixu::Camera_Movement::BACKWARD,
                                             delta_time);
    if (input == "LEFT")
        first_person_camera->ProcessKeyboard(taixu::Camera_Movement::LEFT,
                                             delta_time);
    if (input == "RIGHT")
        first_person_camera->ProcessKeyboard(taixu::Camera_Movement::RIGHT,
                                             delta_time);
}
void Renderer::processInput(glm::vec2 mouse_pos) {

    if (first_mouse) {
        last_x      = mouse_pos.x;
        last_y      = mouse_pos.y;
        first_mouse = false;
    }

    float xoffset = mouse_pos.x - last_x;
    float yoffset =
            last_y -
            mouse_pos.y;// reversed since y-coordinates go from bottom to top

    last_x = mouse_pos.x;
    last_y = mouse_pos.y;

    first_person_camera->ProcessMouseMovement(xoffset, yoffset);
}
void Renderer::processInput(float scroll_yoffset) {
    first_person_camera->ProcessMouseScroll(scroll_yoffset);
}
}// namespace taixu