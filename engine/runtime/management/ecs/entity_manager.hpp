//
// Created by xmmmmmovo on 2023/4/28.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_ENTITY_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_ENTITY_MANAGER_HPP

#include <cstdint>
#include <queue>

namespace taixu {
// A simple type alias
using Entity = std::uint32_t;

// Used to define the size of arrays later on
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;

constexpr ComponentType MAX_COMPONENTS = 32;
using Signature                        = std::bitset<MAX_COMPONENTS>;

class EntityManager final {
private:
    std::queue<Entity>                  _available_entities{};
    std::array<Signature, MAX_ENTITIES> _signatures{};
    std::uint32_t                       _living_entity_count{};

public:
    explicit EntityManager();
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_ENTITY_MANAGER_HPP
