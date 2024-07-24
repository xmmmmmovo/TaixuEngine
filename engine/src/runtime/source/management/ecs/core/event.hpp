//
// Created by xmmmmmovo on 2023/5/2.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_EVENT_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_EVENT_HPP

#include <any>
#include <cstdint>
#include <unordered_map>

namespace taixu {

using EventIdType = std::uint32_t;
using ParamIdType = std::uint32_t;

class Event final {
private:
    EventIdType                               _event_type;
    std::unordered_map<EventIdType, std::any> _params;

public:
    Event() = delete;

    explicit Event(const EventIdType type) : _event_type(type) {}

    [[nodiscard]] EventIdType GetEventType() const noexcept;

    template<typename T>
    void AddParam(EventIdType id, T&& param) {
        _params.emplace(id, std::forward<T>(param));
    }

    template<typename T>
    T& GetParam(const EventIdType id) {
        return std::any_cast<T&>(_params[id]);
    }
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_EVENT_HPP
