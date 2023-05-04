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
    std::queue<EntityType>                  _available_entities{};
    std::array<SignatureType, MAX_ENTITIES> _signatures{};
    std::uint32_t                           _living_entity_count{};

public:
    explicit EntityManager();

    [[nodiscard]] EntityType createEntity();

    void destroyEntity(EntityType entity);

    void setSignature(EntityType entity, SignatureType const &signature);

    [[nodiscard]] SignatureType getSignature(EntityType entity);
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_ENTITY_MANAGER_HPP
