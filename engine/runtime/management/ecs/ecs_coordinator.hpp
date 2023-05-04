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
    void init() {
        _component_manager = std::make_unique<ComponentManager>();
        _entity_manager    = std::make_unique<EntityManager>();
        _event_manager     = std::make_unique<EventManager>();
    }

    // Entity methods
    EntityType CreateEntity() { return _entity_manager->createEntity(); }

    void DestroyEntity(EntityType entity) {
        _entity_manager->destroyEntity(entity);
        _component_manager->entityDestroyed(entity);
    }

    // Component methods
    template<typename T>
    void RegisterComponent() {
        _component_manager->registerComponent<T>();
    }

    template<typename T>
    void AddComponent(EntityType entity, T component) {
        _component_manager->AddComponent<T>(entity, component);

        auto signature = _entity_manager->getSignature(entity);
        signature.set(_component_manager->GetComponentType<T>(), true);
        _entity_manager->setSignature(entity, signature);
    }

    template<typename T>
    void RemoveComponent(EntityType entity) {
        _component_manager->RemoveComponent<T>(entity);

        auto signature = _entity_manager->getSignature(entity);
        signature.set(_component_manager->GetComponentType<T>(), false);
        _entity_manager->setSignature(entity, signature);
    }

    template<typename T>
    T &GetComponent(EntityType entity) {
        return _component_manager->getComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType() {
        return _component_manager->GetComponentType<T>();
    }

    // Event methods
    void AddEventListener(EventIdType                         eventId,
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
