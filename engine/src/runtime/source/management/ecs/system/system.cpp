//
// Created by xmmmmmovo on 1/27/2024.
//

#include "system.hpp"

namespace taixu {


void System::addEntity(const Entity entity) {
    if (hasEntity(entity)) { return; }
    _entities_set.insert(entity);
    _entities.push_back(entity);
}

void System::removeEntity(const Entity entity) {
    if (!hasEntity(entity)) { return; }
    _entities_set.erase(entity);
    if (const auto found_iter = std::ranges::find(_entities, entity);
        found_iter != _entities.end()) {
        std::swap(_entities.back(), *found_iter);
        _entities.pop_back();
    }
}

bool System::hasEntity(const Entity entity) const {
    return _entities_set.contains(entity);
}


}// namespace taixu