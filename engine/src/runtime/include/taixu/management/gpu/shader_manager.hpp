//
// Created by xmmmmmovo on 1/28/2024.
//
#pragma once

#include <array>

#include <magic_enum.hpp>

#include "common/base/hash.hpp"
#include "management/render/tx_shader.hpp"

namespace taixu {

enum class TXBuiltinShader : uint8_t {
    FORWARD_VERT = 0,
    FORWARD_FRAG = 1,
};

static constexpr std::size_t TX_BUILTIN_SHADER_SIZE = magic_enum::enum_count<TXBuiltinShader>();

using TXBuiltinShaderCreateInfoArrT = std::array<TXShaderModuleCreateInfo, TX_BUILTIN_SHADER_SIZE>;
using TXBuiltinShaderModulePtrArrT  = std::array<std::shared_ptr<TXShaderModule>, TX_BUILTIN_SHADER_SIZE>;


#define INIT_BUILTIN_SHADER_MODULE_CREATE_INFO(name_, binaries_, size, type, stage_, infos)                            \
    {                                                                                                                  \
        auto& info         = (infos)[static_cast<size_t>(name_)];                                                      \
        info.name          = magic_enum::enum_name(name_);                                                             \
        info.binaries      = binaries_;                                                                                \
        info.binaries_size = size;                                                                                     \
        info.source_type   = type;                                                                                     \
        info.stage         = (stage_);                                                                                 \
    }

class TXShaderModuleManager final {
private:
    TX_INLINE static TXBuiltinShaderCreateInfoArrT builtin_shader_create_infos;
    TX_INLINE static TXBuiltinShaderModulePtrArrT  builtin_modules;

    std::unordered_map<hash32_t, std::shared_ptr<TXShaderModule>> _custom_modules;

    [[nodiscard]] std::shared_ptr<TXShaderModule> createShaderModuleInner(TXShaderModuleCreateInfo const& info) const;

public:
    void init();

    [[nodiscard]] std::shared_ptr<TXShaderModule> createCustomShaderModule(const TXShaderModuleCreateInfo& info) const;

    [[nodiscard]] std::shared_ptr<TXShaderModule> getBuiltinShaderModule(TXBuiltinShader builtin_shader) const;
};


}// namespace taixu
