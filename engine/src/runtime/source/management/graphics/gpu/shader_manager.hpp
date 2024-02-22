//
// Created by xmmmmmovo on 1/28/2024.
//
#pragma once

#include "common/base/hash.hpp"
#include <array>

#include <magic_enum.hpp>

#include "management/graphics/rhi/tx_shader.hpp"

namespace taixu {

enum class EnumTXBuiltinShader : uint8_t {
    FORWARD_VERT = 0,
    FORWARD_FRAG = 1,
};

static constexpr std::size_t TX_BUILTIN_SHADER_SIZE =
        magic_enum::enum_count<EnumTXBuiltinShader>();

using TXBuiltinShaderCreateInfoArrT =
        std::array<TXShaderModuleCreateInfo, TX_BUILTIN_SHADER_SIZE>;
using TXBuiltinShaderModulePtrArrT =
        std::array<std::shared_ptr<TXShaderModule>, TX_BUILTIN_SHADER_SIZE>;


#define INIT_BUILTIN_SHADER_MODULE_CREATE_INFO(name_, binaries_, size, type,   \
                                               stage_, infos)                  \
    {                                                                          \
        auto& info         = (infos)[static_cast<size_t>(name_)];              \
        info.name          = magic_enum::enum_name(name_);                     \
        info.binaries      = binaries_;                                        \
        info.binaries_size = size;                                             \
        info.source_type   = type;                                             \
        info.stage         = (stage_);                                         \
    }

#define INIT_BUILTIN_SHADER_MODULE_CREATE_INFO_ATTR_DESC(name_, attr)          \
    {                                                                          \
        auto& info        = (infos)[static_cast<size_t>(name_)];               \
        info.in_attr_desc = (attr);                                            \
    }


class TXShaderModuleAdapter {
public:
    virtual std::shared_ptr<TXShaderModule>
    create(TXShaderModuleCreateInfo const& info) = 0;
    virtual void
    initForBuiltinShaderCreateInfo(TXBuiltinShaderCreateInfoArrT& infos) = 0;

    explicit TXShaderModuleAdapter() = default;
    virtual ~TXShaderModuleAdapter() = default;
};

class TXShaderModuleManager final {
private:
    TX_INLINE static TXBuiltinShaderCreateInfoArrT _builtin_shader_create_infos;
    TX_INLINE static TXBuiltinShaderModulePtrArrT  _builtin_modules;

    std::unordered_map<hash32_t, std::shared_ptr<TXShaderModule>>
            _custom_modules;

    using AdapterPtrT = std::unique_ptr<TXShaderModuleAdapter>;
    AdapterPtrT _adapter{};

    [[nodiscard]] std::shared_ptr<TXShaderModule>
    createShaderModuleInner(TXShaderModuleCreateInfo const& info) const;

public:
    void init(AdapterPtrT&& adapter);

    std::shared_ptr<TXShaderModule>
    createCustomShaderModule(const TXShaderModuleCreateInfo& info);

    [[nodiscard]] std::shared_ptr<TXShaderModule>
    getBuiltinShaderModule(EnumTXBuiltinShader builtin_shader) const;
};


}// namespace taixu