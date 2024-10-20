//
// Created by xmmmmmovo on 11/21/2023.
//

#pragma once

#include "taixu/common/base/macro.hpp"
#include "taixu/common/log/logger.hpp"

#include <functional>
#include <memory>

TX_NAMESPACE_BEGIN

template<typename RegisterKeyT, typename ProductionT, typename... CreateArgsT>
class AbstractFactory {
private:
    using creation_func_t = std::function<std::unique_ptr<ProductionT>(CreateArgsT...)>;

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

    static std::unique_ptr<ProductionT> createProduct(RegisterKeyT key, CreateArgsT&&... args) {
        decltype(auto) iter = creation_func_map.find(key);

        if (creation_func_map.end() == iter) {
            FATAL_LOG("Cannot create the unsupported {}", typeid(RegisterKeyT).name());
            return nullptr;
        }
        return iter->second(std::forward<CreateArgsT>(args)...);
    }
};

TX_NAMESPACE_END
