//
// Created by xmmmmmovo on 1/18/2024.
//

#pragma once

#include "common/hal/tx_string.hpp"
#include "taixu/common/designs/noncopyable.hpp"

#include <memory>

namespace taixu {

enum class EnumTextureFormat : uint8_t {
    R8G8B8A8_UNORM,
    R8G8B8A8_SRGB,
};

enum class EnumTextureBindingFlags { SHADER_BINDING };

struct TXTexture2DCreateInfo {
    tx_string               name{};
    uint32_t                width{0};
    uint32_t                height{0};
    EnumTextureFormat       format{};
    uint32_t                mip_levels{1};
    uint32_t                sampler{1};
    EnumTextureBindingFlags flags{};
};

class TXTexture2D : std::enable_shared_from_this<TXTexture2D>, Noncopyable {};

}// namespace taixu
