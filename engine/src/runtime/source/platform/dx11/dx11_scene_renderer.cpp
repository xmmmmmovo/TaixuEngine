//
// Created by xmmmmmovo on 1/7/2024.
//

#include "dx11_scene_renderer.hpp"

#include "dx11_shader.hpp"
#include "dx11_trace.hpp"

#include <backends/imgui_impl_dx11.h>

namespace taixu {

DX11SceneRenderer::~DX11SceneRenderer() = default;

void DX11SceneRenderer::updateScene(float delta_time, Scene* scene) {
    _swap_chain.clearWindow();

    // 首先先set states
    // TODO: 删除
    _context.device_context()->RSSetViewports(1, &_swap_chain.view_port());

    // 渲染逻辑
    _context.device_context()->Draw(3, 0);
}

void DX11SceneRenderer::imguiForGraphicsAPIInit() {
    ImGui_ImplDX11_Init(_context.device().Get(),
                        _context.device_context().Get());
}

void DX11SceneRenderer::imguiGraphicsPreUpdate() { ImGui_ImplDX11_NewFrame(); }

void DX11SceneRenderer::imguiGraphicsUpdate() {
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void DX11SceneRenderer::imguiGraphicsDestroy() { ImGui_ImplDX11_Shutdown(); }

void DX11SceneRenderer::presentToWindow() { _swap_chain.presentToWindow(); }

void DX11SceneRenderer::initForGraphicsAPI(Window* window) {
    _context.init(window);
    _swap_chain.init(&_context, window);

    std::unique_ptr<DX11ShaderModuleAdapter> adapter =
            std::make_unique<DX11ShaderModuleAdapter>(&_context);
    _shader_module_manager.init(std::move(adapter));

    vert = std::dynamic_pointer_cast<DX11ShaderModule<ID3D11VertexShader>>(
            _shader_module_manager.getBuiltinShaderModule(
                    EnumTXBuiltinShader::FORWARD_VERT));
    frag = std::dynamic_pointer_cast<DX11ShaderModule<ID3D11PixelShader>>(
            _shader_module_manager.getBuiltinShaderModule(
                    EnumTXBuiltinShader::FORWARD_FRAG));

    // 设置三角形顶点
    V vertices[] = {{Vec3(0.0f, 0.5f, 0.5f), Vec4(0.0f, 1.0f, 0.0f, 1.0f)},
                    {Vec3(0.5f, -0.5f, 0.5f), Vec4(0.0f, 0.0f, 1.0f, 1.0f)},
                    {Vec3(-0.5f, -0.5f, 0.5f), Vec4(1.0f, 0.0f, 0.0f, 1.0f)}};

    buffer = DX11Buffer::create(
            &_context,
            {.size         = sizeof vertices,
             .data_ptr     = vertices,
             .usage        = EnumTXBufferUsage::VERTEX_BUFFER,
             .memory_usage = EnumTXBufferMemoryUsage::GPU_READ_ONLY});

    // 输入装配阶段的顶点缓冲区设置
    UINT stride = sizeof(V);// 跨越字节数
    UINT offset = 0;        // 起始偏移量

    _context.device_context()->IASetVertexBuffers(
            0, 1, buffer->getBufferAddressOf(), &stride, &offset);
    // 设置图元类型，设定输入布局
    _context.device_context()->IASetPrimitiveTopology(
            D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _context.device_context()->IASetInputLayout(vert->getInputLayoutPtr());
    // 将着色器绑定到渲染管线
    _context.device_context()->VSSetShader(vert->getShaderPtr(), nullptr, 0);
    _context.device_context()->PSSetShader(frag->getShaderPtr(), nullptr, 0);
}

void DX11SceneRenderer::destroyGraphicsAPI() {}

}// namespace taixu
