//
// Created by xmmmmmovo on 1/20/2024.
//

#ifndef TX_RENDERPASS_HPP_47FA985BC7AF4FCE8F53970861177E7D
#define TX_RENDERPASS_HPP_47FA985BC7AF4FCE8F53970861177E7D

#include "common/designs/noncopyable.hpp"
#include <memory>

namespace taixu {

class TXRenderPassNode : public std::enable_shared_from_this<TXRenderPassNode>,
                         private Noncopyable {};

}// namespace taixu

#endif// TX_RENDERPASS_HPP_47FA985BC7AF4FCE8F53970861177E7D
