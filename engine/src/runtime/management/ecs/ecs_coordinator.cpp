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

Entity ECSCoordinator::createEntity() {
    return _entity_manager->createEntity();
}

void ECSCoordinator::destroyEntity(Entity entity) {
    _entity_manager->destroyEntity(entity);
    _component_manager->entityDestroyed(entity);
    _system_manager->entityDestroyed(entity);
}

std::uint32_t ECSCoordinator::getEntityCount() const {
    return _entity_manager->livingEntityCount();
}

System *ECSCoordinator::registerSystem(SystemIdType systemId) {
    return _system_manager->registerSystem(systemId);
}

void ECSCoordinator::setsystemSignature(SystemIdType     systemId,
                                        Signature const &signature) {
    _system_manager->setSignature(systemId, signature);
}

void ECSCoordinator::addEventListener(
        EventIdType eventId, const std::function<void(Event &)> &listener) {
    _event_manager->addListener(eventId, listener);
}

void ECSCoordinator::removeEventListener(EventIdType eventId) {
    this->_event_manager->removeListener(eventId);
}

void ECSCoordinator::sendEvent(Event &event) {
    _event_manager->addEvent(event);
}

void ECSCoordinator::sendEvent(EventIdType eventId) {
    _event_manager->addEvent(eventId);
}

void ECSCoordinator::update() { this->_event_manager->processEvents(); }

}// namespace taixu
