//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "interface/component.hpp"

#include "frag_frag.h"
#include "graphics/render/shader.hpp"
#include "vert_vert.h"

namespace taixu::editor {
// 暂时先这么写，只是测试用，以后会改
// 暂时先这么写，只是测试用，以后会改
// 暂时先这么写，只是测试用，以后会改

static cg::ShaderProgram *shaderProgram;
// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
static float                     vertices[] = {
        -0.5f, -0.5f, 0.0f,// left
        0.5f,  -0.5f, 0.0f,// right
        0.0f,  0.5f,  0.0f // top
};
static unsigned int VBO, VAO;
static unsigned int fbo, bufferTexId, rbo;
static ImVec2       size = {1366, 768};

class RenderComponent : public IComponent {
public:
    void init() override {
        shaderProgram = new cg::ShaderProgram(VERT_VERT, FRAG_FRAG);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              (void *) 0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);

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
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, bufferTexId, 0);

        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(
                GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x,
                size.y);// use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  rbo);// now actually attach it
        GLenum buffers[4] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(bufferTexId, buffers);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void update() override {
        glBindFramebuffer(GL_FRAMEBUFFER, bufferTexId);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram->use();
        glBindVertexArray(
                VAO);// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ImGui::Begin("Scene");

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        size                     = {viewportPanelSize.x, viewportPanelSize.y};
        // Because I use the texture from OpenGL, I need to invert the V from the UV.
        ImGui::Image(reinterpret_cast<void *>(bufferTexId), size, ImVec2(0, 1),
                     ImVec2(1, 0));
        ImGui::End();
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_RENDER_COMPONENT_HPP
