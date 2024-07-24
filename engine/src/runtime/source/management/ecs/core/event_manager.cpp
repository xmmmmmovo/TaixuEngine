//
// Created by xmmmmmovo on 2023/5/2.
//

#include "event_manager.hpp"

namespace taixu {

void EventManager::addListener(EventIdType                        event_type,
                               const std::function<void(Event&)>& listener) {

    _listeners[event_type] = listener;
}

void EventManager::removeListener(EventIdType event_type) {
    _listeners.erase(event_type);
}

void EventManager::addEvent(const Event& event) { _event_queue.push(event); }

void EventManager::addEvent(EventIdType event_type) {
    _event_queue.emplace(event_type);
}

void EventManager::processEvents() {
    while (!_event_queue.empty()) {

        if (auto& event = _event_queue.front();
            _listeners.contains(event.GetEventType())) {
            _listeners[event.GetEventType()](event);
        }

        _event_queue.pop();
    }
}

}// namespace taixu