//
// Created by xmmmmmovo on 1/26/2024.
//

#include "dx11_shader.hpp"

#include <d3d11_1.h>

#include "management/graphics/gpu/shaders/shader_inc_list.hpp"

namespace taixu {

std::shared_ptr<TXShaderModule>
DX11ShaderModuleAdapter::create(const TXShaderModuleCreateInfo& info) {
    return std::shared_ptr<TXShaderModule>();
}

void DX11ShaderModuleAdapter::initForBuiltinShaderCreateInfo(
        TXBuiltinShaderCreateInfoArrT& infos) {


#define INIT_DX11_BUILTIN_SHADER_MODULE_CREATE_INFO(name, stage, var_name)     \
    INIT_BUILTIN_SHADER_MODULE_CREATE_INFO(                                    \
            EnumTXBuiltinShader::name, EnumShaderStage::stage, var_name,       \
            sizeof(var_name), EnumShaderSourceType::HLSL, infos)

    INIT_DX11_BUILTIN_SHADER_MODULE_CREATE_INFO(TRIANGLE_VERT, VERTEX,
                                                TRIANGLE_VERT_DX11);
    INIT_DX11_BUILTIN_SHADER_MODULE_CREATE_INFO(TRIANGLE_FRAG, FRAGMENT,
                                                TRIANGLE_FRAG_DX11);
}


DX11ShaderModule::DX11ShaderModule(EnumShaderStage type, const char* source) {}

DX11ShaderModule::~DX11ShaderModule() {}

}// namespace taixu