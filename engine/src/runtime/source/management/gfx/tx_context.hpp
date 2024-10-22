/**
 * @file tx_context.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "taixu/common/designs/noncopyable.hpp"
#include "taixu/gameplay/gui/window.hpp"

namespace taixu {

class TXContext : public Noncopyable, public std::enable_shared_from_this<TXContext> {
private:
    RenderAPI _api{RenderAPI::VULKAN};

public:
    static std::unique_ptr<TXContext> create(const Window* window, RenderAPI api);
};

}// namespace taixu
