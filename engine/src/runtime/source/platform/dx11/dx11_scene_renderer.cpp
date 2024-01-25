//
// Created by xmmmmmovo on 1/7/2024.
//

#include "dx11_scene_renderer.hpp"

namespace taixu {

void DX11SceneRenderer::init(Window* window) {
    _context.init(window);
    _swap_chain.init(&_context, window);
}

void DX11SceneRenderer::update(float delta_time, Scene* scene) {

    _swap_chain.presentToWindow();
}

void DX11SceneRenderer::destory() {}

DX11SceneRenderer::~DX11SceneRenderer() = default;

}// namespace taixu
