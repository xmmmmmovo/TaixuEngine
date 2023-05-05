
namespace taixu {

template<typename T>
void ComponentArray<T>::insertData(EntityType entity, T &&component) {
    assert(_entity_to_index_map.find(entity) == _entity_to_index_map.end() &&
           "Component added to same entity more than once.");

    // Put new entry at end and update the maps
    size_t new_index                = _size;
    _entity_to_index_map[entity]    = new_index;
    _index_to_entity_map[new_index] = entity;
    _component_array[new_index]     = std::move(component);
    ++_size;
}

template<typename T>
void ComponentArray<T>::removeData(EntityType entity) {
    assert(_entity_to_index_map.find(entity) != _entity_to_index_map.end() &&
           "Removing non-existent component.");

    // Copy element at end into deleted element's place to maintain density
    size_t index_of_removed_entity = _entity_to_index_map[entity];
    size_t index_of_last_element   = _size - 1;
    // TODO: 尝试使用move修复
    _component_array[index_of_removed_entity] =
            std::move(_component_array[index_of_last_element]);

    // Update map to point to moved spot
    EntityType entity_of_last_element =
            _index_to_entity_map[index_of_last_element];
    _entity_to_index_map[entity_of_last_element]  = index_of_removed_entity;
    _index_to_entity_map[index_of_removed_entity] = entity_of_last_element;

    _entity_to_index_map.erase(entity);
    _index_to_entity_map.erase(index_of_last_element);

    --_size;
}

template<typename T>
T &ComponentArray<T>::getData(EntityType entity) {
    assert(_entity_to_index_map.find(entity) != _entity_to_index_map.end() &&
           "Retrieving non-existent component.");

    // Return a reference to the entity's component
    return _component_array[_entity_to_index_map[entity]];
}

}// namespace taixu