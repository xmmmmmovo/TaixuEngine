//
// Created by xmmmmmovo on 2023/2/14.
//

#include "renderer.hpp"


#include "gui/input_system.hpp"


namespace taixu {
void Renderer::initialize() {
    loadAPI(this->api);
    render_context = std::make_shared<RenderContext>();

    render_context->initialize();

    //Bind buffer for each Mesh

    render_context->bindMesh(
            render_context->getSwapContext()->getData()->sphere->meshes[0],"sphere");
       
    render_context->bindMesh(
            render_context->getSwapContext()->getData()->model->meshes[0],"teapot");     
    
}

void Renderer::tick(float delta_time) {
    clock.update();
    // render_context->bindMesh(
    //         render_context->getSwapContext()->getData()->sphere->meshes[0],"sphere");
    // render_context->rebindMesh(
    //         render_context->getSwapContext()->getData()->sphere->meshes[0]);
    render_context->framebuffer->bind();
    render_context->sphere_context->clear();
    render_context->bindShader();

    render_context->tickbyMesh(
           render_context->getSwapContext()->sphere->meshes[0],"sphere");

    // render_context->tickbyMesh(
    //        render_context->getSwapContext()->model->meshes[0],"teapot");

    
    render_context->framebuffer->unbind();
}

void Renderer::clear() {}

void Renderer::resize(float width, float height) {
    size.x = width;
    size.y = height;
    render_context->resize(width,height);
}

}// namespace taixu