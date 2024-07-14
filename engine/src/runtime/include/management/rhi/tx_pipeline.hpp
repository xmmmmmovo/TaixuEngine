//
// Created by xmmmmmovo on 1/19/2024.
//

#pragma once

#include "tx_shader.hpp"
#include <cstdint>

#include "common/base/macro.hpp"
#include "common/designs/noncopyable.hpp"
#include "common/math/vec.hpp"

#include <memory>

namespace taixu {

enum class EnumPipelineType : uint8_t { GRAPHICS, ASYNC_COMPUTE };

struct TXViewport {
    float x{0.0f};
    float y{0.0f};
    float width{0.0f};
    float height{0.0f};
    float min_depth{0.0f};
    float max_depth{0.0f};
};

struct TXScissor {
    Vec2 offset{};
    Vec2 extent{};
};

struct TXPipelineMultisampleStateCreateInfo {};

struct TXPipelineDepthStencilStateCreateInfo {};

struct TXPipelineColorBlendStateCreateInfo {};

struct TXPipelineRaterizationStateCreateInfo {
    bool depth_clamp_enable{false};
    bool rasterizer_discard_enable{false};
    bool depth_bias_enable{false};
    bool depth_bias_clamp_enable{false};
};

struct TXPipelineCreateInfo {
    std::vector<std::shared_ptr<TXShaderModule>> modules{};
    TXViewport                                   viewport{};
    TXScissor                                    scissor{};
    TXPipelineMultisampleStateCreateInfo         multisample_state{};
    TXPipelineDepthStencilStateCreateInfo        depth_stencil_state{};
    TXPipelineColorBlendStateCreateInfo          color_blend_state{};
    TXPipelineRaterizationStateCreateInfo        raterization_state{};
};

class TXPipeline : public std::enable_shared_from_this<TXPipeline>,
                   private Noncopyable {};

}// namespace taixu
