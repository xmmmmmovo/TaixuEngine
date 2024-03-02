//
// Created by xmmmmmovo on 1/26/2024.
//

#include "dx11_shader.hpp"

#include <d3d11_1.h>

#include "common/log/logger.hpp"
#include "dx11_trace.hpp"
#include "management/gpu/shaders/intern/shader_inc_list.hpp"

namespace taixu {

DXGI_FORMAT attributeFormat2DxgiFormat(EnumAttributeFormat format) {
    switch (format) {
        case EnumAttributeFormat::R8G8B8A8_FLOAT:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case EnumAttributeFormat::R32G32B32A32_FLOAT:
            return DXGI_FORMAT_R32G32B32A32_FLOAT;
        case EnumAttributeFormat::R32G32B32_FLOAT:
            return DXGI_FORMAT_R32G32B32_FLOAT;
        case EnumAttributeFormat::R32G32_FLOAT:
            return DXGI_FORMAT_R32G32_FLOAT;
        case EnumAttributeFormat::R32_FLOAT:
            return DXGI_FORMAT_R32_FLOAT;
    }
    return DXGI_FORMAT_R32G32B32A32_FLOAT;
}

D3D11_INPUT_CLASSIFICATION
attributeUsage2DX11InputClassify(EnumAttributeUsage usage) {
    switch (usage) {
        case EnumAttributeUsage::VERTEX:
            return D3D11_INPUT_PER_VERTEX_DATA;
        case EnumAttributeUsage::INSTANCE:
            return D3D11_INPUT_PER_INSTANCE_DATA;
    }
    return D3D11_INPUT_PER_VERTEX_DATA;
}
uint32_t attributeFormatSize(EnumAttributeFormat format) {
    switch (format) {
        case EnumAttributeFormat::R8G8B8A8_FLOAT:
            [[fallthrough]];
        case EnumAttributeFormat::R32G32B32A32_FLOAT:
            return 16;
        case EnumAttributeFormat::R32G32B32_FLOAT:
            return 12;
        case EnumAttributeFormat::R32G32_FLOAT:
            return 8;
        case EnumAttributeFormat::R32_FLOAT:
            return 4;
    }
    return 0;
}

DX11ShaderModuleAdapter::DX11ShaderModuleAdapter(DX11Context* context)
    : _context(context) {}

std::shared_ptr<TXShaderModule>
DX11ShaderModuleAdapter::create(const TXShaderModuleCreateInfo& info) {
    if (info.source_type == EnumShaderSourceType::GLSL) {
        ERROR_LOG("Unsupported shader source type: GLSL");
        return nullptr;
    } else if (info.source_type == EnumShaderSourceType::HLSL) {
        HRESULT hr;
        /// create scope macro
#define SHADER_CREATE_SCOPE(ShaderType)                                         \
    ComPtrT<ID3D11##ShaderType##Shader> shader;                                 \
    hr = _context->device()->Create##ShaderType##Shader(                        \
            info.binaries, info.binaries_size, nullptr,                         \
            shader.GetAddressOf());                                             \
    HR_FAILED_GOTO(hr, "Failed to create vertex shader: {}", info.name);        \
                                                                                \
    if (info.stage == EnumShaderStage::VERTEX &&                                \
        info.in_attr_desc.has_value()) {                                        \
                                                                                \
        const auto                            attrs = info.in_attr_desc->attrs; \
        std::vector<D3D11_INPUT_ELEMENT_DESC> in_attr_desc;                     \
        in_attr_desc.reserve(attrs.size());                                     \
        uint32_t offset = 0;                                                    \
        for (const auto& attr : attrs) {                                        \
            in_attr_desc.push_back({                                            \
                    .SemanticName  = attr.name.data(),                          \
                    .SemanticIndex = 0,                                         \
                    .Format        = attributeFormat2DxgiFormat(attr.format),   \
                    .InputSlot     = 0,                                         \
                    .AlignedByteOffset = offset,                                \
                    .InputSlotClass =                                           \
                            attributeUsage2DX11InputClassify(attr.usage),       \
                    .InstanceDataStepRate = 0,                                  \
            });                                                                 \
            offset += attributeFormatSize(attr.format);                         \
        }                                                                       \
                                                                                \
        ComPtrT<ID3D11InputLayout> input_layout_ptr{nullptr};                   \
                                                                                \
        hr = _context->device()->CreateInputLayout(                             \
                in_attr_desc.data(), static_cast<UINT>(in_attr_desc.size()),    \
                info.binaries, info.binaries_size,                              \
                input_layout_ptr.GetAddressOf());                               \
        HR_FAILED_GOTO(hr, "Failed to create input layout");                    \
                                                                                \
        return std::make_shared<DX11ShaderModule<ID3D11##ShaderType##Shader>>(  \
                std::move(shader), std::move(input_layout_ptr), info);          \
    }                                                                           \
                                                                                \
    return std::make_shared<DX11ShaderModule<ID3D11##ShaderType##Shader>>(      \
            std::move(shader), nullptr, info);
        /// macro end

        switch (info.stage) {
            case EnumShaderStage::FRAGMENT: {
                SHADER_CREATE_SCOPE(Pixel);
            }
            case EnumShaderStage::VERTEX: {
                SHADER_CREATE_SCOPE(Vertex);
            }
            case EnumShaderStage::GEOMETRY: {
                SHADER_CREATE_SCOPE(Geometry);
            }
            case EnumShaderStage::HULL: {
                SHADER_CREATE_SCOPE(Hull);
            }
            case EnumShaderStage::DOMAINS: {
                SHADER_CREATE_SCOPE(Domain);
            }
            case EnumShaderStage::COMPUTE: {
                SHADER_CREATE_SCOPE(Compute);
            }
        }
    }

failed:
    return nullptr;
}

void DX11ShaderModuleAdapter::initForBuiltinShaderCreateInfo(
        TXBuiltinShaderCreateInfoArrT& infos) {

#define INIT_DX11_BUILTIN_SHADER_MODULE_CREATE_INFO(name, var_name, stage)     \
    INIT_BUILTIN_SHADER_MODULE_CREATE_INFO(name, var_name, sizeof(var_name),   \
                                           EnumShaderSourceType::HLSL,         \
                                           EnumShaderStage::stage, infos)

    INIT_DX11_BUILTIN_SHADER_MODULE_CREATE_INFO(
            EnumTXBuiltinShader::FORWARD_VERT, FORWARD_VERT_DX11, VERTEX);
    INIT_BUILTIN_SHADER_MODULE_CREATE_INFO_ATTR_DESC(
            EnumTXBuiltinShader::FORWARD_VERT,
            (TXShaderModuleInAttrDesc{
                    .attrs = {{"POSITION", EnumAttributeFormat::R32G32B32_FLOAT,
                               EnumAttributeUsage::VERTEX},
                              {"COLOR", EnumAttributeFormat::R32G32B32A32_FLOAT,
                               EnumAttributeUsage::VERTEX}}}));
    INIT_DX11_BUILTIN_SHADER_MODULE_CREATE_INFO(
            EnumTXBuiltinShader::FORWARD_FRAG, FORWARD_FRAG_DX11, FRAGMENT);
}

}// namespace taixu