//
// Created by xmmmmmovo on 2023/4/29.
//

#include "ecs_coordinator.hpp"

namespace taixu {

void ECSCoordinator::AddEventListener(
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
