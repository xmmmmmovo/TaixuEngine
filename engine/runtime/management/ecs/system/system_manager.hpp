//
// Created by xmmmmmovo on 2023/5/5.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_MANAGER_HPP

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "system.hpp"

namespace taixu {

class SystemManager final {
private:
    std::unordered_map<SystemIdType, Signature>               _signatures{};
    std::unordered_map<SystemIdType, std::unique_ptr<System>> _categories{};

public:
    System *registerCategory(SystemIdType const key) {
        assert(_categories.find(key) == _categories.end() &&
               "Registering system more than once.");

        auto [iter, was_insert] =
                _categories.insert({key, std::make_unique<System>()});
        return iter->second.get();
    }

    void setSignature(SystemIdType const key, Signature const &signature) {
        assert(_categories.find(key) != _categories.end() &&
               "System used before registered.");
        _signatures.insert({key, signature});
    }

    void entityDestroyed(Entity entity) {
        for (auto const &pair : _categories) {
            auto const &cate = pair.second;
            cate->removeEntity(entity);
        }
    }

    void entitySignatureChanged(Entity entity, Signature entitySignature) {
        for (auto const &pair : _categories) {
            auto const &key                = pair.first;
            auto const &category           = pair.second;
            auto const &category_signature = _signatures[key];

            if ((entitySignature & category_signature) == category_signature) {
                category->addEntity(entity);
            } else {
                category->addEntity(entity);
            }
        }
    }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_MANAGER_HPP
