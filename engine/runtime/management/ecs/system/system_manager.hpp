//
// Created by xmmmmmovo on 2023/5/5.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_MANAGER_HPP

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "management/ecs/core/ecs_types.hpp"
#include "system.hpp"

namespace taixu {

class SystemManager final {
private:
    std::unordered_map<SystemIdType, Signature>               _signatures{};
    std::unordered_map<SystemIdType, std::unique_ptr<System>> _systems{};

public:
    System *registerSystem(SystemIdType const key) {
        assert(_systems.find(key) == _systems.end() &&
               "Registering system more than once.");

        auto [iter, was_insert] =
                _systems.insert({key, std::make_unique<System>()});
        return iter->second.get();
    }

    void setSignature(SystemIdType const key, Signature const &signature) {
        assert(_systems.find(key) != _systems.end() &&
               "System used before registered.");
        _signatures.insert({key, signature});
    }

    Signature const &getSignature(SystemIdType const key) {
        assert(_systems.find(key) != _systems.end() &&
               "System used before registered.");
        return _signatures[key];
    }

    void entityDestroyed(Entity entity) {
        for (auto const &pair : _systems) {
            auto const &cate = pair.second;
            cate->removeEntity(entity);
        }
    }

    void entitySignatureChanged(Entity entity, Signature entitySignature) {
        for (auto const &pair : _systems) {
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
