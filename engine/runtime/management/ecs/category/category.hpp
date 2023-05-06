//
// Created by xmmmmmovo on 2023/5/5.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_HPP

#include "core/base/macro.hpp"
#include "management/ecs/core/ecs_types.hpp"

#include <algorithm>
#include <unordered_set>
#include <vector>

namespace taixu {

struct Category final {
    PROTOTYPE_ONLY_GETTER(private, std::vector<Entity>, entities)

private:
    std::unordered_set<Entity> _entities_set{};

public:
    inline void addEntity(Entity entity) {
        if (hasEntity(entity)) { return; }
        _entities_set.insert(entity);
        _entities.push_back(entity);
    }

    inline void removeEntity(Entity entity) {
        if (!hasEntity(entity)) { return; }
        _entities_set.erase(entity);
        if (auto found_iter =
                    std::find(_entities.begin(), _entities.end(), entity);
            found_iter != _entities.end()) {
            std::swap(_entities.back(), *found_iter);
            _entities.pop_back();
        }
    }

    inline bool hasEntity(Entity entity) {
        return _entities_set.find(entity) != _entities_set.end();
    }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_CATEGORY_CATEGORY_HPP
