//
// Created by xmmmmmovo on 2023/4/29.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP

#include <memory>

#include "management/ecs/system/component_array.hpp"
#include "management/ecs/system/component_manager.hpp"
#include "management/ecs/system/event.hpp"
#include "management/ecs/system/event_manager.hpp"
#include "system/component_manager.hpp"
#include "system/entity_manager.hpp"

namespace taixu {

/**
 * @brief ECS协调器,用于协调各个系统,以及管理组件.
 * @details
 * ECS Coordinator, used to coordinate various systems and manage components.
 * 其中包含system中的四个部件: ComponentManager, EntityManager, SystemManager, EventManager
 */
class ECSCoordinator {
public:
    void init();

    // Entity methods
    EntityType createEntity();

    void destroyEntity(EntityType entity);

    /// Component methods ///

    template<typename T>
    void registerComponent() {
        _component_manager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(EntityType entity, T &&component) {
        _component_manager->addComponent<T>(entity, std::forward<T>(component));

        auto signature = _entity_manager->getSignature(entity);
        signature.set(_component_manager->GetComponentType<T>(), true);
        _entity_manager->setSignature(entity, signature);
    }

    template<typename T>
    void removeComponent(EntityType entity) {
        _component_manager->removeComponent<T>(entity);

        auto signature = _entity_manager->getSignature(entity);
        signature.set(_component_manager->GetComponentType<T>(), false);
        _entity_manager->setSignature(entity, signature);
    }

    template<typename T>
    T &getComponent(EntityType entity) {
        return _component_manager->getComponent<T>(entity);
    }

    template<typename T>
    ComponentType getComponentType() {
        return _component_manager->GetComponentType<T>();
    }

    // Event methods
    void addEventListener(EventIdType                         eventId,
                          std::function<void(Event &)> const &listener);

    void removeEventListener(EventIdType eventId);

    void sendEvent(Event &event);

    void sendEvent(EventIdType eventId);

    void update();

private:
    std::unique_ptr<ComponentManager> _component_manager{nullptr};
    std::unique_ptr<EntityManager>    _entity_manager{nullptr};
    std::unique_ptr<EventManager>     _event_manager{nullptr};
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
