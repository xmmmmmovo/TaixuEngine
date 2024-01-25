//
// Created by xmmmmmovo on 1/19/2024.
//

#ifndef TX_SWAPCHAIN_HPP_CE0743299870403FA655FBDE9A487C83
#define TX_SWAPCHAIN_HPP_CE0743299870403FA655FBDE9A487C83

#include "common/base/macro.hpp"
#include "common/designs/noncopyable.hpp"

namespace taixu {

template<typename SwapChainT, typename ViewPortT>
class TXSwapChain : private Noncopyable {
    PROTOTYPE_ONLY_GETTER(protected, SwapChainT, swap_chain);
    PROTOTYPE_ONLY_GETTER(protected, ViewPortT, view_port);
};

}// namespace taixu

#endif// TX_SWAPCHAIN_HPP_CE0743299870403FA655FBDE9A487C83
