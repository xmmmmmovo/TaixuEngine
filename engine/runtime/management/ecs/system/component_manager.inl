

namespace taixu {

template<typename T>
void ComponentManager::registerComponent() {
    const char *type_name = typeid(T).name();

    assert(_component_types.find(type_name) == _component_types.end() &&
           "Registering component type more than once.");

    // Add this component type to the component type map
    _component_types.insert({type_name, _next_component_type});

    // Create a ComponentArray pointer and add it to the component arrays map
    _component_arrays.insert(
            {type_name, std::make_shared<ComponentArray<T>>()});

    // Increment the value so that the next component registered will be different
    ++_next_component_type;
}

inline void ComponentManager::entityDestroyed(EntityType entity) {
    // Notify each component array that an entity has been destroyed
    // If it has a component for that entity, it will remove it
    for (auto const &pair : _component_arrays) {
        auto const &component = pair.second;

        component->entityDestroyed(entity);
    }
}

template<typename T>
std::weak_ptr<ComponentArray<T>> ComponentManager::getComponentArray() {
    const char *type_name = typeid(T).name();

    assert(_component_types.find(type_name) != _component_types.end() &&
           "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(
            _component_arrays[type_name]);
}

}// namespace taixu