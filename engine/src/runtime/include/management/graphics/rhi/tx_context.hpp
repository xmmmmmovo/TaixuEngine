//
// Created by xmmmmmovo on 1/13/2024.
//

#ifndef ENGINE_SRC_RUNTIME_INCLUDE_MANAGEMENT_GRAPHICS_RHI_TX_CONTEXT_7D8E49B3281B4EBD88252DB03FB61B8A
#define ENGINE_SRC_RUNTIME_INCLUDE_MANAGEMENT_GRAPHICS_RHI_TX_CONTEXT_7D8E49B3281B4EBD88252DB03FB61B8A
#include "common/base/macro.hpp"
#include "tx_device.hpp"
#include "tx_swapchain.hpp"
#include <type_traits>

namespace taixu {

template<TXDevice DeviceT, typename Context, TXSwapChain SwapChainT>
class TXContext : private Noncopyable {
    PROTOTYPE(private, DeviceT, device);
    PROTOTYPE(private, Context, context);
    PROTOTYPE(private, SwapChainT, swapchain);

public:
    virtual void init() = 0;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_INCLUDE_MANAGEMENT_GRAPHICS_RHI_TX_CONTEXT_7D8E49B3281B4EBD88252DB03FB61B8A
