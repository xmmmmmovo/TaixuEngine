//
// Created by xmmmmmovo on 2023/4/29.
//

#include "ecs_coordinator.hpp"
#include "system/system.hpp"
#include "system/system_manager.hpp"

namespace taixu {

void ECSCoordinator::init() {
    _component_manager = std::make_unique<ComponentManager>();
    _entity_manager    = std::make_unique<EntityManager>();
    _event_manager     = std::make_unique<EventManager>();
    _system_manager    = std::make_unique<SystemManager>();
}

Entity ECSCoordinator::createEntity() const {
    return _entity_manager->createEntity();
}

void ECSCoordinator::destroyEntity(const Entity entity) const {
    _entity_manager->destroyEntity(entity);
    _component_manager->entityDestroyed(entity);
    _system_manager->entityDestroyed(entity);
}

std::uint32_t ECSCoordinator::getEntityCount() const {
    return _entity_manager->livingEntityCount();
}

System* ECSCoordinator::registerSystem(const SystemIdType systemId) const {
    return _system_manager->registerSystem(systemId);
}

void ECSCoordinator::setsystemSignature(const SystemIdType systemId,
                                        Signature const&   signature) const {
    _system_manager->setSignature(systemId, signature);
}

void ECSCoordinator::addEventListener(
        const EventIdType                  eventId,
        const std::function<void(Event&)>& listener) const {
    _event_manager->addListener(eventId, listener);
}

void ECSCoordinator::removeEventListener(const EventIdType eventId) const {
    this->_event_manager->removeListener(eventId);
}

void ECSCoordinator::sendEvent(const Event& event) const {
    _event_manager->addEvent(event);
}

void ECSCoordinator::sendEvent(const EventIdType eventId) const {
    _event_manager->addEvent(eventId);
}

void ECSCoordinator::update() const { this->_event_manager->processEvents(); }

}// namespace taixu
