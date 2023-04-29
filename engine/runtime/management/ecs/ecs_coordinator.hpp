//
// Created by xmmmmmovo on 2023/4/29.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP

#include <memory>

#include "management/ecs/system/component_manager.hpp"

namespace taixu {

/**
 * @brief ECS协调器,用于协调各个系统,以及管理组件.
 * @details
 * ECS Coordinator, used to coordinate various systems and manage components.
 * 其中包含system中的四个部件: ComponentManager, EntityManager, SystemManager, EventManager
 */
class ECSCoordinator {
private:
    std::unique_ptr<ComponentManager> _component_manager{nullptr};

public:
    void init();
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
