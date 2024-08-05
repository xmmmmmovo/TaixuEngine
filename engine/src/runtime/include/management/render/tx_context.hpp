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

#include "common/base/resule.hpp"
#include "common/designs/noncopyable.hpp"
#include "common/hal/tx_container.hpp"
#include "gameplay/gui/window.hpp"
#include "tx_device.hpp"

namespace taixu {

class TXContext final : public Noncopyable {
public:
    vk::raii::Instance               _instance{VK_NULL_HANDLE};
    vk::raii::DebugUtilsMessengerEXT _debug_messenger{VK_NULL_HANDLE};

    TXDevice _device{};
};

/**
 *
 * @return get all supported layers and unique them to unordered_set
 */
ResValT<tx_unordered_set<const char*>> getInstanceSupportedLayers();


/**
 *
 * @return get all supported extensions and unique them to unordered_set
 */
ResValT<tx_unordered_set<const char*>> getInstanceSupportedExtensions();


ResValT<vk::raii::Instance>
createInstance(tx_vector<const char*> const&                        enabled_layers,
               tx_vector<const char*> const&                        enabled_extensions,
               std::optional<vk::DebugUtilsMessengerCreateInfoEXT>& info);

ResValT<std::unique_ptr<TXContext>> createTXContext(const Window* window);

}// namespace taixu
