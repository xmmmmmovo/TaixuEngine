//
// Created by xmmmmmovo on 2023/2/14.
//

#include "renderer.hpp"

#include "frag_frag.h"
#include "vert_vert.h"

namespace taixu::cg {
void Renderer::initialize() {
    render_context = std::make_shared<Render_Context>();

    render_context->initialize();

    first_person_camera = std::make_shared<Camera>();

    shaderProgram = new cg::ShaderProgram(VERT_VERT, FRAG_FRAG);

    glGenVertexArrays(1, &VAO);



    //Bind buffer for each Mesh
    render_context->bindBuffer(VAO,VBO,EBO,render_context->getSwapContext()->getData()->model->meshes[0]);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Generate a texture image to store rendering results
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glGenTextures(1, &bufferTexId);
    glBindTexture(GL_TEXTURE_2D, bufferTexId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           bufferTexId, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(
            GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x,
            size.y);// use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, rbo);// now actually attach it
    GLenum buffers[4] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(bufferTexId, buffers);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Renderer::tick(float delta_time) {
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glBindFramebuffer(GL_FRAMEBUFFER, bufferTexId);

    //glBufferData(GL_FRAMEBUFFER,)
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    glBindVertexArray(
            VAO);// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //Draw as meshes
    glDrawElements(GL_TRIANGLES,
                   static_cast<unsigned int>(render_context->getSwapContext()
                                                     ->model->meshes[0].indices.size()),
                   GL_UNSIGNED_INT, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Renderer::clear() {}
void Renderer::resize(float width, float height) {
    size.x = width;
    size.y = height;
}
}// namespace taixu::cg