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
    
}

void Renderer::tick(float delta_time) {
    clock.update();
    
    render_context->render_data->tick();
    render_context->framebuffer->bind();
    
    render_context->render_data->prepared_models[0]->GPU->clear();
    
    render_context->tickbyMesh();

    
    render_context->framebuffer->unbind();
}

void Renderer::clear() {}

void Renderer::resize(float width, float height) {
    size.x = width;
    size.y = height;
    render_context->resize(width,height);
}

}// namespace taixu