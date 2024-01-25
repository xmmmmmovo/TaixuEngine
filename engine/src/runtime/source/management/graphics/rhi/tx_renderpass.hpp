//
// Created by xmmmmmovo on 1/20/2024.
//

#ifndef TX_RENDERPASS_HPP_47FA985BC7AF4FCE8F53970861177E7D
#define TX_RENDERPASS_HPP_47FA985BC7AF4FCE8F53970861177E7D

#include "common/base/macro.hpp"

#include <vector>

namespace taixu {

template<typename RenderTargetViewT, typename DepthStencilTargetViewT,
         typename Texture2DT>
class TXRenderPassNode {
    using ColorTextureVecT = std::vector<Texture2DT>;
    using DepthTextureT    = Texture2DT;

    PROTOTYPE_ONLY_GETTER(protected, RenderTargetViewT, render_target);
    PROTOTYPE_ONLY_GETTER(protected, DepthStencilTargetViewT,
                          depth_stencil_target);

    PROTOTYPE_ONLY_GETTER(protected, DepthTextureT, depth_stencil_texture);
    PROTOTYPE_ONLY_GETTER(protected, ColorTextureVecT,
                          color_target_texture_vec);
};

}// namespace taixu

#endif// TX_RENDERPASS_HPP_47FA985BC7AF4FCE8F53970861177E7D
