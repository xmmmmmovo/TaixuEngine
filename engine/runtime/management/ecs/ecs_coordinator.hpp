//
// Created by xmmmmmovo on 2023/4/29.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP

#include <memory>

#include "core/component_manager.hpp"
#include "core/entity_manager.hpp"
#include "management/ecs/components/camera/camera_component.hpp"
#include "management/ecs/components/renderable/renderable_component.hpp"
#include "management/ecs/components/rigid_body/rigid_body_component.hpp"
#include "management/ecs/components/transform/transform_component.hpp"
#include "management/ecs/core/component_array.hpp"
#include "management/ecs/core/component_manager.hpp"
#include "management/ecs/core/ecs_types.hpp"
#include "management/ecs/core/event.hpp"
#include "management/ecs/core/event_manager.hpp"
#include "management/ecs/system/system.hpp"
#include "management/ecs/system/system_manager.hpp"
#include "resource/json/json_type/world_json.hpp"
#include "resource/manager/asset_manager.hpp"
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
    Entity createEntity();

    void destroyEntity(Entity entity);

    /// Component methods ///

    template<typename T>
    void registerComponent() {
        _component_manager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity entity, T &&component) {
        _component_manager->addComponent<T>(entity, std::forward<T>(component));

        auto signature = _entity_manager->getSignature(entity);
        signature.set(_component_manager->getComponentType<T>(), true);
        _entity_manager->setSignature(entity, signature);

        _system_manager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    void removeComponent(Entity entity) {
        _component_manager->removeComponent<T>(entity);

        auto signature = _entity_manager->getSignature(entity);
        signature.set(_component_manager->getComponentType<T>(), false);
        _entity_manager->setSignature(entity, signature);

        _system_manager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    T &getComponent(Entity entity) {
        return _component_manager->getComponent<T>(entity);
    }

    template<typename... Type>
    [[nodiscard]] bool anyOf(const Entity entity) const {
        return (_component_manager->contains<std::remove_const_t<Type>>(
                        entity) ||
                ...);
    }


    template<typename... Type>
    [[nodiscard]] bool allOf(const Entity entity) const {
        return (_component_manager->contains<std::remove_const_t<Type>>(
                        entity) &&
                ...);
    }

    template<typename T>
    ComponentType getComponentType() {
        return _component_manager->getComponentType<T>();
    }

    System *registerSystem(SystemIdType systemId);

    void setsystemSignature(SystemIdType systemId, Signature const &signature);

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
    std::unique_ptr<SystemManager>    _system_manager{nullptr};
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
