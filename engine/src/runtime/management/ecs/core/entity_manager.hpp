//
// Created by xmmmmmovo on 2023/4/28.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_ENTITY_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_ENTITY_MANAGER_HPP

#include "ecs_types.hpp"
#include <cstdint>
#include <queue>
#include <cassert>

namespace taixu {

class EntityManager final {
private:
    std::queue<Entity>                  _available_entities{};
    std::array<Signature, MAX_ENTITIES> _signatures{};
    std::uint32_t                       _living_entity_count{};

public:
    explicit EntityManager() {
        for (auto i = 0; i < MAX_ENTITIES; ++i) { _available_entities.push(i); }
    }

    [[nodiscard]] Entity createEntity() {
        assert(_living_entity_count < MAX_ENTITIES &&
               "Too many entities in existence.");

        // Take an ID from the front of the queue
        Entity const id = _available_entities.front();
        _available_entities.pop();
        ++_living_entity_count;

        return id;
    }

    void destroyEntity(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // Invalidate the destroyed entity's signature
        _signatures[entity].reset();

        // Put the destroyed ID at the back of the queue
        _available_entities.push(entity);
        --_living_entity_count;
    }

    void setSignature(Entity entity, Signature const &signature) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        _signatures[entity] = signature;
    }

    [[nodiscard]] Signature getSignature(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        return _signatures[entity];
    }

    [[nodiscard]] std::uint32_t livingEntityCount() const {
        return _living_entity_count;
    }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_ENTITY_MANAGER_HPP
