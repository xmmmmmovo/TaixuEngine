//
// Created by xmmmmmovo on 1/25/2024.
//

#pragma once


#include <cstdint>
#include <memory>

#include "common/base/macro.hpp"

namespace taixu {

enum class EnumShaderStage : uint8_t {
    NONE = 0,
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    COMPUTE,
    DOMAINT,
    HULL,
    TEXTURE
};

enum class EnumShaderSourceType : uint8_t { NONE = 0, GLSL, SPIRV, HLSL };

struct TXShaderModuleCreateInfo {
    EnumShaderStage      stage{EnumShaderStage::NONE};
    EnumShaderSourceType source_type{EnumShaderSourceType::NONE};
    const uint8_t*       binaries{nullptr};
    size_t               binaries_size{0};
};

class TXShaderModule : std::enable_shared_from_this<TXShaderModule> {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, EnumShaderStage, stage,
                                      EnumShaderStage::NONE);
};


}// namespace taixu