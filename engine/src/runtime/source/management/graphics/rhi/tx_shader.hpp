//
// Created by xmmmmmovo on 1/25/2024.
//

#pragma once

#include <cstdint>
#include <memory>

namespace taixu {

enum class EnumShaderStage : uint8_t {
    FRAGMENT,
    VERTEX,
    GEOMETRY,
    HULL,
    DOMAINS,
    COMPUTE,
};

enum class EnumShaderSourceType : uint8_t { NONE = 0, GLSL, SPIRV, HLSL };

enum class EnumAttributeFormat : uint8_t {
    R8G8B8A8_FLOAT,
    R32G32B32A32_FLOAT,
    R32G32B32_FLOAT,
    R32G32_FLOAT,
    R32_FLOAT,
};

enum class EnumAttributeUsage : uint8_t {
    VERTEX,
    INSTANCE,
};

struct TXShaderModuleInAttrDesc {
    struct InputAttr {
        std::string_view    name{};
        EnumAttributeFormat format{};
        EnumAttributeUsage  usage{};
    };

    std::vector<InputAttr> attrs{};
};

struct TXShaderModuleCreateInfo {
    std::string_view     name{};
    const uint8_t*       binaries{nullptr};
    size_t               binaries_size{0};
    EnumShaderSourceType source_type{EnumShaderSourceType::NONE};
    EnumShaderStage      stage{};

    std::optional<TXShaderModuleInAttrDesc> in_attr_desc{std::nullopt};
};

class TXShaderModule : public std::enable_shared_from_this<TXShaderModule> {
protected:
    EnumShaderStage _stage{};

public:
    explicit TXShaderModule(TXShaderModuleCreateInfo const& info)
        : _stage{info.stage} {};

    EnumShaderStage getShaderStage() const { return _stage; }

    virtual ~TXShaderModule() = default;
};

}// namespace taixu