//
// Created by xmmmmmovo on 2023/5/5.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_MANAGER_HPP

#include <memory>
#include <unordered_map>

#include "system.hpp"
#include <management/ecs/core/ecs_types.hpp>

namespace taixu {

class SystemManager final {
private:
    std::unordered_map<SystemIdType, Signature>               _signatures{};
    std::unordered_map<SystemIdType, std::unique_ptr<System>> _systems{};

public:
    System* registerSystem(SystemIdType key);

    void setSignature(SystemIdType key, Signature const& signature);

    Signature const& getSignature(SystemIdType key);

    void entityDestroyed(Entity entity);

    void entitySignatureChanged(Entity entity, Signature entitySignature);
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_MANAGER_HPP
