//
// Created by xmmmmmovo on 2023/4/28.
//

#include "entity_manager.hpp"

taixu::EntityManager::EntityManager() {
    for (auto i = 0; i < MAX_ENTITIES; ++i) { _available_entities.push(i); }
}
