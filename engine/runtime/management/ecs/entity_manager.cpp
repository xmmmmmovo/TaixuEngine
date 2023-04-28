//
// Created by xmmmmmovo on 2023/4/28.
//

#include "entity_manager.hpp"

taixu::EntityManager::EntityManager() {
    for (auto i = 0; i < MAX_ENTITIES; ++i) { _available_entities.push(i); }
}
taixu::Entity taixu::EntityManager::createEntity() {
    assert(_living_entity_count < MAX_ENTITIES &&
           "Too many entities in existence.");

    // Take an ID from the front of the queue
    Entity const id = _available_entities.front();
    _available_entities.pop();
    ++_living_entity_count;

    return id;
}

void taixu::EntityManager::destroyEntity(taixu::Entity entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Invalidate the destroyed entity's signature
    _signatures[entity].reset();

    // Put the destroyed ID at the back of the queue
    _available_entities.push(entity);
    --_living_entity_count;
}

void taixu::EntityManager::setSignature(taixu::Entity    entity,
                                        taixu::Signature signature) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    _signatures[entity] = signature;
}

taixu::Signature taixu::EntityManager::getSignature(taixu::Entity entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    return _signatures[entity];
}
