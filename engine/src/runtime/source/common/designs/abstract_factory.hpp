//
// Created by xmmmmmovo on 11/21/2023.
//

#ifndef ENGINE_SRC_COMMON_DESIGNS_FACTORY_FC367611E24C4563B569D839E1FD8984
#define ENGINE_SRC_COMMON_DESIGNS_FACTORY_FC367611E24C4563B569D839E1FD8984

#include "common/base/macro.hpp"
#include "common/log/logger.hpp"

#include <functional>
#include <memory>

namespace taixu {

template<typename RegisterKeyT, typename ProductionT>
class AbstractFactory {
private:
    using creation_func_t = std::function<std::unique_ptr<ProductionT>()>;

protected:
    TX_INLINE static std::unordered_map<RegisterKeyT, creation_func_t> creation_func_map{};

public:
    static bool registerCreationFunc(RegisterKeyT key, creation_func_t func) {
        TX_ASSERT_MSG(func, "func is nullptr");
        auto iter = creation_func_map.find(key);

        if (iter != creation_func_map.end()) {
            WARN_LOG("This _window have already registered");
            iter->second = std::move(func);
            return true;
        } else {
            creation_func_map.emplace(key, std::move(func));
            return true;
        }

        return false;
    }

    static std::unique_ptr<ProductionT> createProduct(RegisterKeyT key) {
        decltype(auto) iter = creation_func_map.find(key);

        if (creation_func_map.end() == iter) {
            FATAL_LOG("Cannot create the unsupported {}", typeid(RegisterKeyT).name());
            return nullptr;
        }
        return iter->second();
    }
};

}// namespace taixu

#endif// ENGINE_SRC_COMMON_DESIGNS_FACTORY_FC367611E24C4563B569D839E1FD8984
