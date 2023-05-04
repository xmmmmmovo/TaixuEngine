#ifndef TAIXUENGINE_ENTITY_COMPONENT
#define TAIXUENGINE_ENTITY_COMPONENT

#include <cstdint>
#include <typeinfo>
#include <unordered_map>

#include "core/base/macro.hpp"
#include "management/ecs/object/guid_genenrator.hpp"
#include "management/ecs/system/entity_manager.hpp"

namespace taixu {

class IComponentArray {
public:
    virtual ~IComponentArray()                      = default;
    virtual void entityDestroyed(EntityType entity) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray {
public:
    void insertData(EntityType entity, T component) {
        assert(_entity_to_index_map.find(entity) ==
                       _entity_to_index_map.end() &&
               "Component added to same entity more than once.");

        // Put new entry at end and update the maps
        size_t new_index                = _size;
        _entity_to_index_map[entity]   = new_index;
        _index_to_entity_map[new_index] = entity;
        _component_array[new_index]     = component;
        ++_size;
    }

    void removeData(EntityType entity) {
        assert(_entity_to_index_map.find(entity) !=
                       _entity_to_index_map.end() &&
               "Removing non-existent component.");

        // Copy element at end into deleted element's place to maintain density
        size_t index_of_removed_entity = _entity_to_index_map[entity];
        size_t index_of_last_element   = _size - 1;
        _component_array[index_of_removed_entity] =
                _component_array[index_of_last_element];

        // Update map to point to moved spot
        EntityType entity_of_last_element =
                _index_to_entity_map[index_of_last_element];
        _entity_to_index_map[entity_of_last_element]  = index_of_removed_entity;
        _index_to_entity_map[index_of_removed_entity] = entity_of_last_element;

        _entity_to_index_map.erase(entity);
        _index_to_entity_map.erase(index_of_last_element);

        --_size;
    }

    T &getData(EntityType entity) {
        assert(_entity_to_index_map.find(entity) !=
                       _entity_to_index_map.end() &&
               "Retrieving non-existent component.");

        // Return a reference to the entity's component
        return _component_array[_entity_to_index_map[entity]];
    }

    void entityDestroyed(EntityType entity) override {
        if (_entity_to_index_map.find(entity) != _entity_to_index_map.end()) {
            // Remove the entity's component if it existed
            removeData(entity);
        }
    }

private:
    // The packed array of components (of generic type T),
    // set to a specified maximum amount, matching the maximum number
    // of entities allowed to exist simultaneously, so that each entity
    // has a unique spot.
    std::array<T, MAX_ENTITIES> _component_array;

    // Map from an entity ID to an array index.
    std::unordered_map<EntityType, size_t> _entity_to_index_map;

    // Map from an array index to an entity ID.
    std::unordered_map<size_t, EntityType> _index_to_entity_map;

    // Total size of valid entries in the array.
    size_t _size{};
};

}// namespace taixu

#include "component_array.inl"

#endif /* TAIXUENGINE_ENTITY_COMPONENT */
