//
// Created by xmmmmmovo on 2023/4/29.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP

#include <memory>

#include "management/ecs/entity_component/entity_component.hpp"
#include "management/ecs/system/component_manager.hpp"
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
    void Init() {
        mComponentManager = std::make_unique<ComponentManager>();
        mEntityManager    = std::make_unique<EntityManager>();
    }


    // Entity methods
    Entity CreateEntity() { return mEntityManager->createEntity(); }

    void DestroyEntity(Entity entity) {
        mEntityManager->destroyEntity(entity);

        mComponentManager->EntityDestroyed(entity);
    }


    // Component methods
    template<typename T>
    void RegisterComponent() {
        mComponentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        mComponentManager->AddComponent<T>(entity, component);

        auto signature = mEntityManager->getSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), true);
        mEntityManager->setSignature(entity, signature);

        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        mComponentManager->RemoveComponent<T>(entity);

        auto signature = mEntityManager->getSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), false);
        mEntityManager->setSignature(entity, signature);

        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T &GetComponent(Entity entity) {
        return mComponentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType() {
        return mComponentManager->GetComponentType<T>();
    }

    // System methods
    template<typename T>
    std::shared_ptr<T> RegisterSystem() {
        return mSystemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature) {
        mSystemManager->SetSignature<T>(signature);
    }


    // Event methods
    void AddEventListener(EventId                             eventId,
                          std::function<void(Event &)> const &listener) {
        mEventManager->AddListener(eventId, listener);
    }

    void SendEvent(Event &event) { mEventManager->SendEvent(event); }

    void SendEvent(EventId eventId) { mEventManager->SendEvent(eventId); }

private:
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<EntityManager>    mEntityManager;
    std::unique_ptr<EventManager>     mEventManager;
    std::unique_ptr<SystemManager>    mSystemManager;
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_ECS_COORDINATOR_HPP
