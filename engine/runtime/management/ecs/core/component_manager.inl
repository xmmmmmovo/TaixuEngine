

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

template<typename T>
ComponentType ComponentManager::GetComponentType() {
    const char *type_name = typeid(T).name();

    assert(_component_types.find(type_name) != _component_types.end() &&
           "Component not registered before use.");

    // Return this component's type - used for creating signatures
    return _component_types[type_name];
}

template<typename T>
void ComponentManager::addComponent(Entity entity, T &&component) {
    // Add a component to the array for an entity
    getComponentArray<T>().lock()->insertData(entity, std::forward<T>(component));
}

template<typename T>
void ComponentManager::removeComponent(Entity entity) {
    // Remove a component from the array for an entity
    getComponentArray<T>().lock()->removeData(entity);
}

template<typename T>
T &ComponentManager::getComponent(Entity entity) {
    // Get a reference to a component from the array for an entity
    return getComponentArray<T>().lock()->getData(entity);
}

inline void ComponentManager::entityDestroyed(Entity entity) {
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