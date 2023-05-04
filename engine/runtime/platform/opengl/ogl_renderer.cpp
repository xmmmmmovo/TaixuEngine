//
// Created by xmmmmmovo on 2023/4/6.
//

#include "ogl_renderer.hpp"
#include "glm/fwd.hpp"
#include "spdlog/spdlog.h"

namespace taixu {

constexpr std::array<float, 3> CLEAR_COLOR{0.5294117647f, 0.8078431373f,
                                           0.9215686275f};

const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

float vertices[] = {
        -0.5f, -0.5f, 0.0f,// left
        0.5f,  -0.5f, 0.0f,// right
        0.0f,  0.5f,  0.0f // top
};

unsigned int shaderProgram{0};
unsigned int VBO, VAO;

void OGLRenderer::init() {
    this->_framebuffer = std::make_unique<OGLFrameBuffer>(
            IFrameBufferSpecification{FrameColorImageFormat::RGBA,
                                      FrameDepthImageFormat::DEPTH24STENCIL8});

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

void OGLRenderer::update() {
    _framebuffer->bind();
    clear(CLEAR_COLOR);
    //    if (_current_scene != nullptr) {
    //        _current_scene->shader_program->use();
    //
    //        glm::mat4 const p = _current_scene->_camera->getProjectionMatrix();
    //        glm::mat4 const v = _current_scene->_camera->getViewMatrix();
    //
    //        for (auto const &entity : _current_scene->_renderable_entities) {
    //            auto &renderable =
    //                    _current_scene->ecs_coordinator
    //                            .getComponent<RenderableComponent>(entity);
    //
    //            for (auto &mesh : renderable.meshes) {
    //                mesh.vao->bind();
    //                glm::mat4 m = glm::mat4(1.0f);
    //                m           = glm::translate(m, glm::vec3(0.0f, 0.0f, 0.0f));
    //                glm::mat3 const mv33 = glm::mat3(v * m);
    //                glm::mat4 const MVP  = p * v * m;
    //                _current_scene->shader_program->set_uniform("MVP", MVP);
    //                _current_scene->shader_program->set_uniform("MV3x3", mv33);
    //                _current_scene->shader_program->set_uniform("M", m);
    //                _current_scene->shader_program->set_uniform("V", v);
    //
    //                glDrawArrays(GL_TRIANGLES, 0, mesh.index_count);
    //                mesh.vao->unbind();
    //            }
    //        }
    //    }

    // draw our first triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);

    _framebuffer->unbind();
}

void OGLRenderer::clear(const std::array<float, 3> &color) {
    glClearColor(color[0], color[1], color[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLRenderer::clearSurface() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

IFrameBuffer *OGLRenderer::getRenderFramebuffer() { return _framebuffer.get(); }

}// namespace taixu