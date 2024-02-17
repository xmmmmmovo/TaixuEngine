//
// Created by xmmmmmovo on 1/26/2024.
//

#pragma once

#include "dx11_context.hpp"
#include "management/graphics/gpu/shader_manager.hpp"
#include "management/graphics/rhi/tx_shader.hpp"

namespace taixu {

DXGI_FORMAT attributeFormat2DxgiFormat(EnumAttributeFormat format);

D3D11_INPUT_CLASSIFICATION
attributeUsage2DX11InputClassify(EnumAttributeUsage usage);

uint32_t attributeFormatSize(EnumAttributeFormat format);

class DX11ShaderModuleAdapter final : public TXShaderModuleAdapter {
private:
    DX11Context* _context{nullptr};

public:
    explicit DX11ShaderModuleAdapter(DX11Context* context);
    ~        DX11ShaderModuleAdapter() override = default;

    std::shared_ptr<TXShaderModule>
         create(const TXShaderModuleCreateInfo& info) override;
    void initForBuiltinShaderCreateInfo(
            TXBuiltinShaderCreateInfoArrT& infos) override;
};

template<typename T>
concept DX11ShaderConceptT = std::is_base_of_v<ID3D11DeviceChild, T>;

template<DX11ShaderConceptT DX11ShaderT>
class DX11ShaderModule final : public TXShaderModule {
private:
    ComPtrT<DX11ShaderT>       _shader_ptr{nullptr};
    ComPtrT<ID3D11InputLayout> _input_layout_ptr{nullptr};

public:
    explicit DX11ShaderModule(ComPtrT<ID3D11DeviceChild>&&    shader,
                              ComPtrT<ID3D11InputLayout>&&    input_layout_ptr,
                              TXShaderModuleCreateInfo const& info)
        : TXShaderModule(info), _input_layout_ptr(input_layout_ptr) {
        shader.As(&_shader_ptr);
    }

    ~DX11ShaderModule() override = default;

    DX11ShaderT* getShaderPtr() const { return _shader_ptr.Get(); }

    ID3D11InputLayout* getInputLayoutPtr() const {
        return _input_layout_ptr.Get();
    }
};

}// namespace taixu