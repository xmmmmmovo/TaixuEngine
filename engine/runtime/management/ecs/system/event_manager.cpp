//
// Created by xmmmmmovo on 2023/5/2.
//

#include "event_manager.hpp"

namespace taixu {

void EventManager::AddListener(EventIdType                         event_type,
                               const std::function<void(Event &)> &listener) {

    _listeners[event_type] = listener;
}

void EventManager::RemoveListener(EventIdType event_type) {
    _listeners.erase(event_type);
}

void EventManager::AddEvent(const Event &&event) { _event_queue.push(event); }

void EventManager::ProcessEvents() {
    while (!_event_queue.empty()) {
        auto &event = _event_queue.front();

        if (_listeners.find(event.GetEventType()) != _listeners.end()) {
            _listeners[event.GetEventType()](event);
        }

        _event_queue.pop();
    }
}

}// namespace taixu