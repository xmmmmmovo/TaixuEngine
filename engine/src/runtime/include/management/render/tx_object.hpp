/**
 * @file tx_object.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @version 0.1
 * @date 2024-07-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "common/designs/noncopyable.hpp"

namespace taixu {

template<typename ParentT, typename HandleT>
using vkDestroyFn = void (*)(ParentT, HandleT, vk::AllocationCallbacks const*);

/**
 * @brief RAII vulkan object, using for RAII object.(eg. VkRenderPass,
 * VkDevice...)
 *
 * @tparam ParentT
 * @tparam HandleT
 * @tparam DestroyFnT Delete function, can find them in `volk.h`
 */
template<typename ParentT, typename HandleT,
         vkDestroyFn<ParentT, HandleT> DestroyFnT>
class TXObject final : public Noncopyable {
public:
    explicit TXObject() = default;
    explicit TXObject(HandleT handle, ParentT parent)
        : _handle{handle}, _parent{parent} {}
    ~TXObject() override {
        if (_handle != VK_NULL_HANDLE) {
            TX_ASSERT(_parent != VK_NULL_HANDLE);
            _destroy_fn(_parent, _handle, nullptr);
        }
    }
    [[nodiscard]] HandleT getHandle() const { return _handle; }

private:
    HandleT _handle{VK_NULL_HANDLE};
    ParentT _parent{VK_NULL_HANDLE};
};
}// namespace taixu