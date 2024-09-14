//
// Created by xmmmmmovo on 2023/5/5.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_HPP

#include <unordered_set>
#include <vector>

#include <taixu/common/base/macro.hpp>

#include "management/ecs/core/ecs_types.hpp"

namespace taixu {

struct System final {
    PROTOTYPE_ONLY_GETTER(private, std::vector<Entity>, entities)

private:
    std::unordered_set<Entity> _entities_set{};

public:
    void addEntity(Entity entity);

    void removeEntity(Entity entity);

    [[nodiscard]] bool hasEntity(Entity entity) const;
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_HPP
