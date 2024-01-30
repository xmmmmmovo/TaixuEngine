//
// Created by xmmmmmovo on 1/26/2024.
//

#pragma once

#include "management/graphics/gpu/shader_manager.hpp"
#include "management/graphics/rhi/tx_shader.hpp"

namespace taixu {

struct IDX11Shader {};

struct DX11VertexShader : public IDX11Shader {};

class DX11ShaderModuleAdapter : public TXShaderModuleAdapter {
public:
    std::shared_ptr<TXShaderModule>
         create(const TXShaderModuleCreateInfo& info) override;
    void initForBuiltinShaderCreateInfo(
            TXBuiltinShaderCreateInfoArrT& infos) override;
};

class DX11ShaderModule : public TXShaderModule {

public:
    DX11ShaderModule(EnumShaderStage type, const char* source);

    ~DX11ShaderModule();
};

}// namespace taixu