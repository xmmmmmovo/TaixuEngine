//
// Created by xmmmmmovo on 1/7/2024.
//

#include "dx11_scene_renderer.hpp"

#include "dx11_shader.hpp"
#include "dx11_trace.hpp"

namespace taixu {

void DX11SceneRenderer::init(Window* window) {
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
    // 设置顶点缓冲区描述
    D3D11_BUFFER_DESC vbd;
    ZeroMemory(&vbd, sizeof(vbd));
    vbd.Usage          = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth      = sizeof vertices;
    vbd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    // 新建顶点缓冲区
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertices;
    HR_CHECK(_context.device()->CreateBuffer(&vbd, &InitData,
                                             buffer.GetAddressOf()));

    // 输入装配阶段的顶点缓冲区设置
    UINT stride = sizeof(V);// 跨越字节数
    UINT offset = 0;        // 起始偏移量

    _context.device_context()->IASetVertexBuffers(0, 1, buffer.GetAddressOf(),
                                                  &stride, &offset);
    // 设置图元类型，设定输入布局
    _context.device_context()->IASetPrimitiveTopology(
            D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _context.device_context()->IASetInputLayout(
            vert->getInputLayoutPtr().Get());
    // 将着色器绑定到渲染管线
    _context.device_context()->VSSetShader(vert->getShaderPtr().Get(), nullptr,
                                           0);
    _context.device_context()->PSSetShader(frag->getShaderPtr().Get(), nullptr,
                                           0);
}

void DX11SceneRenderer::update(float delta_time, Scene* scene) {
    _swap_chain.clearWindow();

    _context.device_context()->Draw(3, 0);

    _swap_chain.presentToWindow();
}

void DX11SceneRenderer::destroy() {}

DX11SceneRenderer::~DX11SceneRenderer() = default;

}// namespace taixu
