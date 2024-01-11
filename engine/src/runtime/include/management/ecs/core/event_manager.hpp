//
// Created by xmmmmmovo on 2023/5/2.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_EVENT_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_EVENT_MANAGER_HPP

#include <queue>

#include "event.hpp"

namespace taixu {

class EventManager final {
private:
    std::queue<Event>                                            _event_queue;
    std::unordered_map<EventIdType, std::function<void(Event&)>> _listeners;

public:
    EventManager() = default;

    void addListener(EventIdType                        event_type,
                     const std::function<void(Event&)>& listener);

    void removeListener(EventIdType event_type);

    void addEvent(Event const& event);

    void addEvent(EventIdType event_type);

    void processEvents();
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_EVENT_MANAGER_HPP
