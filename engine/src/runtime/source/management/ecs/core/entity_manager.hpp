//
// Created by xmmmmmovo on 2023/4/28.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_ENTITY_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_ENTITY_MANAGER_HPP

#include "ecs_types.hpp"
#include <cstdint>
#include <queue>

namespace taixu {

class EntityManager final {
private:
    std::queue<Entity>                  _available_entities{};
    std::array<Signature, MAX_ENTITIES> _signatures{};
    std::uint32_t                       _living_entity_count{};

public:
    explicit EntityManager();

    [[nodiscard]] Entity createEntity();

    void destroyEntity(Entity entity);

    void setSignature(Entity entity, Signature const& signature);

    [[nodiscard]] Signature getSignature(Entity entity) const;

    [[nodiscard]] std::uint32_t livingEntityCount() const;
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_ENTITY_MANAGER_HPP
