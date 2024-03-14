//
// Created by xmmmmmovo on 1/20/2024.
//

#ifndef DX11_CORE_HPP_D3FCF82A61A24017BAF5FAA96E603868
#define DX11_CORE_HPP_D3FCF82A61A24017BAF5FAA96E603868

#include "dx11_context.hpp"
#include "dx11_swapchain.hpp"

namespace taixu {

/// 下面的变量必须在renderer里面初始化

/**
 * 全局渲染context
 */
TX_INLINE DX11Context g_dx11_context;

/**
 * 全局swapchain
 */
TX_INLINE DX11SwapChain g_dx11_swap_chain;

}// namespace taixu

#endif// DX11_CORE_HPP_D3FCF82A61A24017BAF5FAA96E603868
