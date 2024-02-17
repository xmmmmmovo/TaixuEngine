//
// Created by xmmmmmovo on 2023/4/29.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP

#include <memory>

#include <management/ecs/core/component_array.hpp>
#include <management/ecs/core/component_manager.hpp>
#include <management/ecs/core/ecs_types.hpp>
#include <management/ecs/core/event.hpp>
#include <management/ecs/core/event_manager.hpp>
#include <management/ecs/system/system.hpp>
#include <management/ecs/system/system_manager.hpp>
#include <resource/manager/asset_manager.hpp>

namespace taixu {

/**
 * @brief ECS协调器,用于协调各个系统,以及管理组件.
 * @details
 * ECS Coordinator, used to coordinate various systems and manage components.
 * 其中包含system中的四个部件: ComponentManager, EntityManager, SystemManager,
 * EventManager
 */
class ECSCoordinator {
public:
    void init();

    /// Entity methods ///
    Entity createEntity() const;

    void destroyEntity(Entity entity) const;

    [[nodiscard]] std::uint32_t getEntityCount() const;

    /// Component methods ///

    template<typename T>
    void registerComponent() const {
        _component_manager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity entity, T&& component) {
        _component_manager->addComponent<T>(entity, std::forward<T>(component));

        auto signature = _entity_manager->getSignature(entity);
        signature.set(_component_manager->getComponentType<T>(), true);
        _entity_manager->setSignature(entity, signature);

        _system_manager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    void removeComponent(const Entity entity) const {
        _component_manager->removeComponent<T>(entity);

        auto signature = _entity_manager->getSignature(entity);
        signature.set(_component_manager->getComponentType<T>(), false);
        _entity_manager->setSignature(entity, signature);

        _system_manager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& getComponent(const Entity entity) {
        return _component_manager->getComponent<T>(entity);
    }

    template<typename T>
    const T& getComponent(const Entity entity) const {
        return _component_manager->getComponent<T>(entity);
    }

    template<typename T>
    [[nodiscard]] ComponentType getComponentType() const {
        return _component_manager->getComponentType<T>();
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


    /// System methods ///
    System* registerSystem(SystemIdType systemId) const;

    void setsystemSignature(SystemIdType     systemId,
                            Signature const& signature) const;

    // Event methods
    void addEventListener(EventIdType                        eventId,
                          std::function<void(Event&)> const& listener) const;

    void removeEventListener(EventIdType eventId) const;

    void sendEvent(const Event& event) const;

    void sendEvent(EventIdType eventId) const;

    void update() const;

private:
    std::unique_ptr<ComponentManager> _component_manager{nullptr};
    std::unique_ptr<EntityManager>    _entity_manager{nullptr};
    std::unique_ptr<EventManager>     _event_manager{nullptr};
    std::unique_ptr<SystemManager>    _system_manager{nullptr};
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
