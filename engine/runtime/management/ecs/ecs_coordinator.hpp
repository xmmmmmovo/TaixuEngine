//
// Created by xmmmmmovo on 2023/4/29.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP

#include <memory>

#include "management/ecs/system/component_manager.hpp"

namespace taixu {

class ECSCoordinator {
private:
    std::unique_ptr<ComponentManager> _component_manager{nullptr};

public:
    void init();
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
