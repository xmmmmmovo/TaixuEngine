//
// Created by xmmmmmovo on 1/18/2024.
//

#pragma once

#include "common/designs/noncopyable.hpp"
#include <memory>

namespace taixu {

enum class EnumTextureFormat {};

struct TXTexture2DCreateInfo {
    uint32_t          width{0};
    uint32_t          height{0};
    EnumTextureFormat format{};
    uint32_t          mip_levels{1};
    uint32_t          sampler{1};
};

class TXTexture2D : std::enable_shared_from_this<TXTexture2D>, Noncopyable {};

}// namespace taixu