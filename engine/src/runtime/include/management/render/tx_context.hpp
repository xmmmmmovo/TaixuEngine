/**
 * @file tx_context.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @version 0.1
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "common/designs/noncopyable.hpp"
#include "common/designs/object.hpp"
#include "gameplay/gui/window.hpp"
#include "tx_device.hpp"

namespace taixu {

class TXContext final : public Noncopyable {
    vk::raii::Instance _instance{VK_NULL_HANDLE};

    TXDevice _device{};
};

vk::raii::Instance createInstance();

ResValT<TXContext> createTXContext(Window* window);

}// namespace taixu
