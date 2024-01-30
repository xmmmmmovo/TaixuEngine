//
// Created by xmmmmmovo on 1/28/2024.
//
#pragma once

#include <array>

#include <magic_enum.hpp>

#include "management/graphics/rhi/tx_shader.hpp"

namespace taixu {

enum class EnumTXBuiltinShader : uint8_t {
    TRIANGLE_VERT = 0,
    TRIANGLE_FRAG = 1,
};
static constexpr std::size_t TX_BUILTIN_SHADER_SIZE =
        magic_enum::enum_count<EnumTXBuiltinShader>();

using TXBuiltinShaderCreateInfoArrT =
        std::array<TXShaderModuleCreateInfo, TX_BUILTIN_SHADER_SIZE>;
using TXBuiltinShaderModulePtrArrT =
        std::array<std::shared_ptr<TXShaderModule>, TX_BUILTIN_SHADER_SIZE>;


#define INIT_BUILTIN_SHADER_MODULE_CREATE_INFO(name, stage_, binaries_, size,  \
                                               type, infos)                    \
    {                                                                          \
        auto& info         = (infos)[static_cast<size_t>(name)];               \
        info.stage         = stage_;                                           \
        info.binaries      = binaries_;                                        \
        info.binaries_size = size;                                             \
        info.source_type   = type;                                             \
    }

class TXShaderModuleAdapter {

public:
    virtual std::shared_ptr<TXShaderModule>
    create(TXShaderModuleCreateInfo const& info) = 0;
    virtual void
    initForBuiltinShaderCreateInfo(TXBuiltinShaderCreateInfoArrT& infos) = 0;

    TXShaderModuleAdapter()          = default;
    virtual ~TXShaderModuleAdapter() = default;
};


class TXShadrModuleManager final {
private:
    static TXBuiltinShaderCreateInfoArrT _builtin_shader_create_infos;
    static TXBuiltinShaderModulePtrArrT  _builtin_modules;

    std::unordered_map<const char*, std::shared_ptr<TXShaderModule>>
            _custom_modules;

    using AdapterPtrT = std::unique_ptr<TXShaderModuleAdapter>;
    AdapterPtrT _adapter;

    std::shared_ptr<TXShaderModule>
    createShaderModuleInner(TXShaderModuleCreateInfo const& info);

public:
    explicit TXShadrModuleManager(AdapterPtrT&& proxy);

    std::shared_ptr<TXShaderModule>
    createShaderModule(TXShaderModuleCreateInfo const& info);

    std::shared_ptr<TXShaderModule>
    getBuiltinShaderModule(EnumTXBuiltinShader builtin_shader);
};


}// namespace taixu