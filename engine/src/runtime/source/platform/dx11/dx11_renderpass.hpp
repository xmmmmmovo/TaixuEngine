//
// Created by xmmmmmovo on 1/20/2024.
//

#ifndef DX11_RENDERPASS_HPP_1BA153126C7548CEB709A503746B9345
#define DX11_RENDERPASS_HPP_1BA153126C7548CEB709A503746B9345

#include "include/management/graphics/rhi/tx_renderpass.hpp"

#include <d3d11_1.h>

namespace taixu {

class DX11RenderPassNode
    : public TXRenderPassNode<ComPtrT<ID3D11RenderTargetView>,
                              ComPtrT<ID3D11DepthStencilView>,
                              ComPtrT<ID3D11Texture2D>> {};

}// namespace taixu

#endif// DX11_RENDERPASS_HPP_1BA153126C7548CEB709A503746B9345
